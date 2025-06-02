import { generateText } from 'ai';

let { AI_key } = "";

import { openai } from '@ai-sdk/openai'; // Ensure OPENAI_API_KEY environment variable is set

const { shape } = "";

const { obj } = "";

filter = function ( vertex ) {

   for( i=0;i<=vertex.length();i+ ) {

        const  vertices = vertex.push( vertex.find("[") );

   };

   return vertices;

};




AI_Key = function() {

  // Openai api key.

  AI_Key = prompt("AI API key :")
  
};



vertices = function (c) {

   const obj = c;

   Module.onRuntimeInitialized = function() {
            console.log("JavaScript: Embind Runtime Initialized!");

            // Create an instance of MyClass from JavaScript
            let myInstance = new Module.MyClass(42);

            console.log(text, myInstance.graph(obj)); // Output: 42

            
            myInstance.delete();
            console.log("Instance deleted.");
  };
}



Identify = function() {

  // Shape identification.

  // Search handler.

  const { shape } = prompt('Shape to define :');

  const { text } = await generateText({
    model: openai('gpt-4o'),
    system: 'You are a friendly assistant!',
    prompt: ('Give me a list of first .obj vertices file for ' + shape + '?'),
  }); 

  const { shape_data } = text.split();

  const { definition } = filter( shape_data );

  const obj = definition;

  // Obj vertices algorithm identification. 

  // Some what mathematical correct.

  // Math.

  Module.onRuntimeInitialized = function() {
              console.log("JavaScript: Embind Runtime Initialized!");

              // Create an instance of MyClass from JavaScript
              let myInstance = new Module.MyClass(42);

              console.log(text, myInstance.graph(obj)); // Output: 42

              
              myInstance.delete();
              console.log("Instance deleted.");
  };


};




UI = function () {

  // Graph UI, data and nodes.

  const newWindow = window.open('', '_blank', 'width=600,height=400');
  newWindow.document.write(`
    <html>
      <head><title>3D graph</title></head>
      <body>
        <h1>Hello, this is your new UI!</h1>
        <p>Created dynamically with JavaScript.</p>
      </body>
    </html>
  `);
  newWindow.document.close();  // Important to finish writing and render the content

  const newWindow = window.open('', '_blank', 'width=600,height=400');
  newWindow.document.write(`
    <html>
      <head><title>Data</title></head>
      <body>
        <h1>Hello, this is your new UI!</h1>
        <p>Created dynamically with JavaScript.</p>
      </body>
    </html>
  `);
  newWindow.document.close();  // Important to finish writing and render the content

  const newWindow = window.open('', '_blank', 'width=600,height=400');
  newWindow.document.write(`
    <html>
      <head><title>Nodes</title></head>
      <body>
        <h1>Hello, this is your new UI!</h1>
        <p>Created dynamically with JavaScript.</p>
      </body>
    </html>
  `);
  newWindow.document.close();  // Important to finish writing and render the content



};



output = function() {

// Output .obj file data.

Module.onRuntimeInitialized = function() {
            console.log("JavaScript: Embind Runtime Initialized!");

            // Create an instance of MyClass from JavaScript
            let myInstance = new Module.MyClass(42);

            console.log(text, myInstance.output(obj)); // Output: 42

            
            myInstance.delete();
            console.log("Instance deleted.");
};


};

current = function() {

      // Current variables set.

      console.log(obj);

};

modules.exports = {
   vertices,
   current,
   output,
   UI,
   Identify,
   AI_Key
};