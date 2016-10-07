var http = require("http");
var url = require("url");

var count = 0;

function onRequest(request, response)
{
  count++;
  console.log("got it\n");

  var path = url.parse(request.url).pathname;
  response.writeHead(200, {"Content-Type" : "text.plain"});
  response.write("hello for " + count + " time. You asked for: " + path);
  response.end();
}

http.createServer(onRequest).listen(8888);
console.log("Server is on");
