import { generateText } from 'ai';

let { AI_key } = "";

// Please install OpenAI SDK first: `npm install openai`

import OpenAI from "openai";

const openai = new OpenAI({
        baseURL: 'https://api.deepseek.com',
        apiKey: AI_key
});

async function main() {
  const completion = await openai.chat.completions.create({
    messages: [{ role: "system", content: "Outer vector data in " + shape + " shape." }],
    model: "deepseek-chat",
  });

}

main();

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

      AI_Key = prompt("AI API key for deepseek :")
      
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

      const { text } = completion.choices[0].message.content

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

                  console.log(text, myInstance.graph(obj, shape)); // Output: 42

                  
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

                  console.log(text, myInstance.output()); // Output: 42

                  
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