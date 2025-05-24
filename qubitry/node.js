<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Embind Example</title>
</head>
<body>
    <script src="embind_example.js"></script>
    <script>
        // 1. Import brain.js

// 1. Import brain.js
// If you're in Node.js:
// const brain = require('brain.js');

// If you're in a browser (assuming you've included it via a <script> tag):
// const brain = window.brain; // or just 'brain' if it's globally available

// For this example, we'll assume a Node.js environment or a modern browser with module support
import brain from 'brain.js';

// 2. Create a new neural network
// We'll use a `NeuralNetwork` for this, which is a feedforward network.
// You can also use `recurrent.LSTM` or `recurrent.RNN` for sequence data.
const net = new brain.NeuralNetwork();

// 3. Prepare your training data
// The format is an array of objects, where each object has 'input' and 'output' properties.
// Input and output values should be arrays of numbers (typically 0s and 1s for binary classification).
const trainingData = [
  { input: [0, 0], output: [0] },
  { input: [0, 1], output: [1] },
  { input: [1, 0], output: [1] },
  { input: [1, 1], output: [0] }
];

// 4. Train the network
// The `train()` method takes the training data and an optional options object.
// Common options:
// - iterations: Maximum number of training iterations (epochs)
// - errorThresh: Target error threshold. Training stops when error falls below this.
// - log: true to log progress to console, or a function for custom logging.
// - logPeriod: How often to log (in iterations).
// - learningRate: How much to adjust weights during training.
// - hiddenLayers: An array defining the number of neurons in each hidden layer.
//                For XOR, one hidden layer is often sufficient.
console.log('Training network...');
const stats = net.train(trainingData, {
  iterations: 20000, // Increase if needed, XOR often converges quickly
  errorThresh: 0.005, // Stop training when error is below this
  log: true, // Log training progress to console
  logPeriod: 1000, // Log every 1000 iterations
  learningRate: 0.

Module.onRuntimeInitialized = function() {
            console.log("JavaScript: Embind Runtime Initialized!");

            // Create an instance of MyClass from JavaScript
            let myInstance = new Module.MyClass(42);

            console.log("Initial X:", myInstance.getX()); // Output: 42

            myInstance.setX(100);
            console.log("New X:", myInstance.getX()); // Output: 100

            let greeting = myInstance.greet("World");
            console.log("Greeting:", greeting); // Output: "Hello, World! My X is 100"

            // Remember to delete instances created in JS if you want to free memory explicitly
            // (though for simple cases, GC will eventually handle it if not stored)
            myInstance.delete();
            console.log("Instance deleted.");
        };
    </script>
</body>
</html>
