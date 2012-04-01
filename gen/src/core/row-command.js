

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
   var echoed_params,
       row_params;

   RowCommand.super_.prototype._parse.apply(this, arguments);

   echoed_params = this.in ? this.in.filter(function(t) { return t.returned; }) : [ ];
   row_params = (raw.responseline && raw.responseline.value) ? (raw.responseline.value.length ? raw.responseline.value : [ raw.responseline.value ]) : [ ];

   this.row = echoed_params.concat(row_params.map(function(parameter) {
      return { name: parameter['@'].name, type: parameter.type, description: parameter.description };
   }));

   if (this.row.length > 0) this.row_type = Types.get(this.name, Types.Row, this.row);
};


RowCommand.create = function(o) { return new RowCommand(o); };




module.exports = RowCommand;
