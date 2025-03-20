#!/bin/bash

echo "Welcome to the quiz!"
sleep 1

# Ask a question
echo "What is the capital of France?"
read answer

if [ "$answer" == "Paris" ]; then
    echo "Correct! 🎉"
else
    echo "Oops! $answer is Wrong  The correct answer is Paris."
fi
