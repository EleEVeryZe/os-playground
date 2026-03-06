const net = require("net");
let s = 0;
let f = 0;
const createConn = () =>
  new Promise((resolve, reject) => {
    const socket = net.createConnection(3000, "127.0.0.1");
    
    socket.on("connect", () => {
       console.log("Sucess: " + s++);
       resolve();
    } );
    socket.on("error", () => {
       console.log("Failure: " + f++);
       reject(); 
    });
  });

(async () => {
  const connections = [];

  for (let i = 0; i < 5000; i++) {
    connections.push(createConn());
  }

  await Promise.allSettled(connections);
})();