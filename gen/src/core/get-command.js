
var _ = require('underscore'),
    util = require('util'),
    Command = require('./command.js').Command;



function GetCommand(raw) {
   this._parse(raw);
}

util.inherits(GetCommand, Command);


GetCommand.create = function(raw) {
   return new GetCommand(raw);
};


module.exports = GetCommand;

