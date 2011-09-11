

var _ = require('underscore'),
    util = require('util'),
    Command = require('./command.js').Command,
    Types = require('./types.js');



function RowCommand(raw) {
   this._parse(raw);
}

util.inherits(RowCommand, Command);


RowCommand.prototype.row = null;

RowCommand.prototype.row_type = null;

RowCommand.prototype._parse = function(raw) {
   RowCommand.super_.prototype._parse.apply(this, arguments);

   if (raw.responseline && raw.responseline.value) {
      var row_parameters = raw.responseline.value.length ? raw.responseline.value : [ raw.responseline.value ];

      this.row_type = Types.get(this.name, row_parameters);

      this.row = _.map(row_parameters, function(parameter) {
         return { name: parameter['@'].name, type: parameter.type, description: parameter.description };
      });
   }
};


RowCommand.create = function(o) { return new RowCommand(o); };




module.exports = RowCommand;
