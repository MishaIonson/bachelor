var net = require('net');
var server = net.createServer(function(connection) {
   console.log('client connected');
   connection.on('end', function() {
      console.log('client disconnected');
   });
   connection.write('Hello World!\r\n');
   connection.pipe(connection);
});
server.listen(8080, function() {
  console.log('server is listening');
});

// var http = require("http");
// var url = require("url");
//
// var count = 0;
//
// function onRequest(request, response)
// {
//   count++;
//   console.log("got it\n");
//
//   var path = url.parse(request.url).pathname;
//   response.writeHead(200, {"Content-Type" : "text.plain"});
//   response.write("hello for " + count + " time. You asked for: " + path);
//   response.end();
// }
//
// http.createServer(onRequest).listen(8888);
// console.log("Server is on");
