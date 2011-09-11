
var fs = require('fs'),
    ejs = require('ejs');

function main(out_directory, types, get_commands, set_commands, row_commands) {

   var in_directory = __dirname + '/templates',
       templates = fs.readdirSync(in_directory);

   templates.forEach(function(template) {
      if (template[0] === '.') return;
      else {
         var out_path = out_directory + '/' + template,
             out = ejs.render(fs.readFileSync(in_directory + '/' + template, 'utf8'), {
                locals: {
                   types: types,
                   get_commands: get_commands,
                   set_commands: set_commands,
                   row_commands: row_commands
                }
             }); 

         console.log('writing out to ' + out_path);

         fs.writeFileSync(out_path, out, 'utf8');
      }
   });

}


module.exports.main = main;
