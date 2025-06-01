import { generateText } from 'ai';
import { openai } from '@ai-sdk/openai'; // Ensure OPENAI_API_KEY environment variable is set


Identify = function() {

const { text } = await generateText({
  model: openai('gpt-4o'),
  system: 'You are a friendly assistant!',
  prompt: 'Define the shape ' + shape + '',
}); 

}

AI_Key = function() {

}

Initiation = function () {

const newWindow = window.open('', '_blank', 'width=600,height=400');
newWindow.document.write(`
  <html>
    <head><title>New UI</title></head>
    <body>
      <h1>Hello, this is your new UI!</h1>
      <p>Created dynamically with JavaScript.</p>
    </body>
  </html>
`);
newWindow.document.close();  // Important to finish writing and render the content


}
