
var fs = require('fs'),
    Types = require('../core/types.js'),
    _ = require('underscore');

var c_types =  { 
      'Number': 'int', 
      'Long': 'long',
      'String': 'char*', 
      'Boolean': 'int',
      'Date': 'df_date', 
      'Time': 'df_time',
      'Address': 'int', 
   },

   type_regexp = {
      'Number': '\\"(-*[0-9]+)\\"',
      'Long': '\\"(-*[0-9]+)\\"',
      'String': '\\"(.*)\\"',
      'Boolean': '\\"([0-1])\\"',
      'Date': '\\"([0-9]+-[0-9]+-[0-9]+)\\"',
      'Time': '\\"([0-9]+:[0-9]+:[0-9]+)\\"',
      'Address': '([0-9]+)'
   },

   type_fmt_string  = {
      'Number': '%d', 
      'Long': '%d',
      'String': '\\"%s\\"', 
      'Boolean': '%d',
      'Date': '\\"%u-%u-%u\\"', 
      'Time': '\\"%u:%u:%u\\"',
      'Address': '%d' 
   },
   
   util = {
      to_c_type: function(type) {
         if (type.type === 'Compound') {
            return type.name + '*';
         } else {
            return c_types[type.type];
         }
      },

      to_regexp: function to_regexp(type) {
         if (type.type === 'Compound') {
            return type.sub_types.map(function(t) { return to_regexp(t); }).join('[[:space:]+]');
         } else {
            return type_regexp[type.type];
         }
      },

      to_fmt_string: function to_fmt_string(type) {
         return type_fmt_string[type];
      },

      to_extraction: function to_extraction(base_var, base_index, compound, t, i) {
         var out = base_var + ((compound) ? '->' + t.name : '');

         i += base_index; /* to bring inline with regexp result */

         if (t.type === 'Number' || t.type === 'Long' || t.type === 'Boolean') { 
            return 'sscanf(rx->subexps[' + i + '].value,"%d",&(' + out + '));';
         } else if (t.type === 'String') { 
            return out + '= formatting_process(rx->subexps[' + i + '].value);';
         } else if (t.type === 'Date') { 
            return 'sscanf(rx->subexps[' + i  + '].value,"%u-%u-%u", &(' + out + '.year), &(' + out + '.month), &(' + out + '.day));';
         } else if (t.type === 'Time') { 
            return 'sscanf(rx->subexps[' + i  + '].value,"%u-%u-%u", &(' + out + '.hours), &(' + out + '.minutes), &(' + out + '.seconds));';
         }
      }
   };


function enrich(command) {
   command.c = {
      in_arguments: command.in ? command.in.map(function(t) { return util.to_c_type(t) + ' ' + t.name; }).join(', ') + ', ' : '',

      out_type: command.out_type ? util.to_c_type(command.out_type) + ', ' : '',

      in_fmt_string: command.in ? ' ' + command.in.map(function(t) { return util.to_fmt_string(t.type); }).join(' ') : '',

      in_fmt_arguments: command.in ? ', ' + command.in.map(function(t) { 
         if (t.type === 'Date') return t.name + '.year, ' + t.name + '.month, ' + t.name + '.day';
         else if (t.type === 'Time') return t.name + '.hours, ' + t.name + '.minutes, ' + t.name + '.seconds';
         else return t.name;
      }).join(', ') : ''
   };

   return command;
}


function main(out_directory, types, get_commands, set_commands, row_commands) {

   var in_directory = __dirname + '/templates',
       templates = fs.readdirSync(in_directory);

   templates.forEach(function(template) {
      if (template[0] === '.') return;
      else {
         var out_path = out_directory + '/' + template,
             out = _.template(fs.readFileSync(in_directory + '/' + template, 'utf8'))({
                util: util,
                types: types,
                get_commands: get_commands.map(enrich),
                set_commands: set_commands.map(enrich),
                row_commands: row_commands.map(enrich)
             }); 

         console.log('writing out to ' + out_path);

         fs.writeFileSync(out_path, out, 'utf8');
      }
   });

}


module.exports.main = main;
