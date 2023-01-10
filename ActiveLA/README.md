# 💪 ActiveLA
CS35L Fall 2022 Final Project 🤓

ActiveLA is a platform that brings sports enthusiasts together.

## Setup instructions
Step 1: Clone the repository.
```
$ git clone https://github.com/TayKaiJun/ActiveLA.git
```
Step 2: Install required dependencies.
```
$ cd server
$ npm install
$ cd ..
$ cd client
$ npm install
```
Step 3: Run the application. The script uses Concurrently to run both the React frontend and the ExpressJS server on the same terminal. 
> The script must be run inside the client directory.
```
$ cd client
$ npm run dev
```
The app uses a .env file to securely store the URI to our MongoDB database. As mentioned in Piazza question @575, the file does not need to be provided as the grader will not be running the project.


