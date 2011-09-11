var sys = require('sys'),
    fs = require('fs'),
    util = require('util'),
    xml2js = require('xml2js'),
    _ = require('underscore'),
    Types = require('./core/types.js'),
    Commands = require('./core/commands.js');

function gen(path, types_path) {
   this.path = path;
   this.types_path = types_path;
}

gen.prototype.run = function() {
   var parser = new xml2js.Parser();

   parser.addListener('end', this._process.bind(this));

   Types.load(this.types_path);

   fs.readFile(this.path, function(err, data) {
      parser.parseString(data);
   });
};

gen.prototype._process = function(result) {
   var version = result['@'].version;

   var row_commands = result.command.filter(function(c) { return c.createsrows === 'True'; }).map(Commands.RowCommand.create),
       get_commands = result.command.filter(function(c) { return !!c.responsevalue; }).map(Commands.GetCommand.create),
       set_commands = result.command.filter(function(c) { return !c.responsevalue; }).map(Commands.SetCommand.create);

   Types.save(this.types_path);

   require('./c-api/entry.js').main(__dirname + '/out', Types.list(), get_commands, set_commands, row_commands);
};

(new gen(__dirname + '/version/commands.xml', __dirname + '/version/types.json')).run();

