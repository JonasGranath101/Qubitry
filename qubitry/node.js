// Example: A simple utility function
function greet(name) {
  return `Hello, ${name}! Welcome to my awesome package.`;
  }

function add(a, b) {
    return a + b;
    }

    // Export the functions you want to make public
    // CommonJS (for Node.js environments and older bundlers)
module.exports = {
      greet,
        add
        };

        // ES Modules (for modern browsers and bundlers)
        // If you are targeting ES modules primarily, you might want to set "type": "module" in package.json
        // export { greet, add };
