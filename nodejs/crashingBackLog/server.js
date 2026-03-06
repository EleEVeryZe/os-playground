const net = require("net");
let d = 0;
const server = net.createServer((socket) => {
  // Simulate slow handling
  setTimeout(() => {
    console.log("DONE!"+ d++);
    socket.end("done");
  }, 10000);
});

server.listen(3000, "0.0.0.0", 1, () => {
  console.log("Server running with backlog=1");
});