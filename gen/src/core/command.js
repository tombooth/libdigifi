

var _ = require('underscore'),
    Types = require('./types.js');

function Command(raw) {
   this._parse(raw);
}

Command.prototype.name = null;

Command.prototype.description = null;

Command.prototype.in = null;

Command.prototype.out = null;

Command.prototype.out_type = null;

Command.prototype._parse = function(raw) {
   var echoed_params,
       out_params;

   this.name = raw['@'].name;
   this.description = raw.description;

   if (raw.parameter) {
      var in_parameters = raw.parameter.length ? raw.parameter : [ raw.parameter ];

      this.in = _.map(in_parameters, function(parameter) {
         return { 
            name: parameter['@'].name,
            type: parameter.type,
            manditory: parameter.manditory === 'True',
            description: parameter.description,
            returned: parameter.useinresponse === 'True'
         };
      });
   }

   echoed_params = this.in ? this.in.filter(function(t) { return t.returned; }) : [ ];
   out_params = raw.responsevalue ? (raw.responsevalue.length ? raw.responsevalue : [ raw.responsevalue ]) : [ ];

   this.out = echoed_params.concat(out_params.map(function(parameter) {
      return { name: parameter['@'].name, type: parameter.type, description: parameter.description };
   }));

   if (this.out.length > 0) this.out_type = Types.get(this.name, Types.Object, this.out);

};

exports.Command = Command;
