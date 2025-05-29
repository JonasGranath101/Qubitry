<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Embind Example</title>
</head>
<body>
    <script src="embind_example.js"></script>
    <script>
        
import { generateText } from 'ai';
import { openai } from '@ai-sdk/openai'; // Ensure OPENAI_API_KEY environment variable is set

const { text } = await generateText({
  model: openai('gpt-4o'),
  system: 'You are a friendly assistant!',
  prompt: 'Why is the sky blue?',
});

Module.onRuntimeInitialized = function() {
            console.log("JavaScript: Embind Runtime Initialized!");

            // Create an instance of MyClass from JavaScript
            let myInstance = new Module.MyClass(42);

            console.log(text, myInstance.getX()); // Output: 42

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
