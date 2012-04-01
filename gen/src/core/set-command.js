
var _ = require('underscore'),
    util = require('util'),
    Command = require('./command.js').Command;



function SetCommand(raw) {
   this._parse(raw);
}

util.inherits(SetCommand, Command);


SetCommand.create = function(raw) {
   return new SetCommand(raw);
};


module.exports = SetCommand;

