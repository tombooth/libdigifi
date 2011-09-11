

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
   this.name = raw['@'].name;
   this.description = raw.description;

   if (raw.parameter) {
      var in_parameters = raw.parameter.length ? raw.parameter : [ raw.parameter ];

      this.in = _.map(in_parameters, function(parameter) {
         return { name: parameter['@'].name, type: parameter.type, description: parameter.description };
      });
   }

   if (raw.responsevalue) {
      var out_parameters = raw.responsevalue.length ? raw.responsevalue : [ raw.responsevalue ];

      this.out = _.map(out_parameters, function(parameter) {
         return { name: parameter['@'].name, type: parameter.type, description: parameter.description };
      });

      this.out_type = Types.get(this.name, out_parameters);
   }
};

exports.Command = Command;
