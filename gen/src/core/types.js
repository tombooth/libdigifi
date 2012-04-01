
var _ = require('underscore'),
    fs = require('fs');

var sig_to_type = { },
    name_to_type = { },
    types = [];


function Type(type, is_row, raw_parameters, signature) {
   types.push(this);

   this.type = type;
   this.is_row = is_row;
   this.name = "type_" + types.length;
   this.signature = signature || Type.signature(is_row, raw_parameters);
   this.methods = [ ];
   this.sub_types = [ ];
}

Type.prototype.name = "";

Type.prototype.signature = null;

Type.prototype.sub_types = null;

Type.prototype.methods = [ ];

Type.prototype.add_method = function(name, parameters) {
   this.methods.push(name);

   _.each(parameters, function(parameter, i) {
      var name = parameter.name,
          sub_type = this.sub_types[i];

      if (sub_type) sub_type.names.push(name);
      else {
         sub_type = this.sub_types[i] = {
            name: name,
            type: parameter.type,
            names: [name],
            description: parameter.description
         };
      }
   }, this);
};

Type.signature = function(is_row, raw_parameters) {
   return (is_row ? 'r' : 'o') + raw_parameters.reduce(function(memo, p) {
      return memo + (p.mandatory ? p.type[0].toUpperCase() : p.type[0].toLowerCase());
   }, '');
};

Type.parse = function(json) {
   var type = sig_to_type[json.signature] = new Type(json.type, json.is_row, null, json.signature);

   type.sub_types = json.sub_types;
   type.methods = json.methods;
   type.name = json.name;

   for (var i = 0, len = json.methods.length; i < len; i++) {
      if (!name_to_type[json.methods[i]]) name_to_type[json.methods[i]] = [ ];
      name_to_type[json.methods[i]].push(type);
   }
};



function load(path) {

   var types_json = fs.readFileSync(path),
       list_of_types = JSON.parse(types_json);

   _.each(list_of_types, Type.parse);

}

function get(name, is_row, parameters) {
   var types = name_to_type[name], type, 
       signature = Type.signature(is_row, parameters);

   if (types && types.length > 0) {
      // as a function could have two types (out and row) associated with it
      // we need to pick out which one we want
      for (var i = 0, len = types.length; i < len; i++) {
         if (types[i].signature == signature) { type = types[i]; break; }
      }
   }

   // if we don't have a mapping from types.json see if a type exists with the same signature
   if (!type) { 
      type = sig_to_type[signature];

      // if none for this methods signature then we need to create a new type
      if (!type) { 
         if (!name_to_type[name]) name_to_type[name] = [ ];

         type = sig_to_type[signature] = name_to_type[name] = 
            new Type((parameters.length > 1) ? "Compound" : parameters[0].type, is_row, parameters, signature);
      }

      type.add_method(name, parameters);
   }

   return type;
}

function list() { return types; }

function save(path) {
   var types_json = JSON.stringify(types, null, 2);

   fs.writeFileSync(path, types_json);
}




module.exports = {

   load: load,
   get: get,
   list: list,
   save: save,

   Type: Type,

   Row: true,
   Object: false

};










