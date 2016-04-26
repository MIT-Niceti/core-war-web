# Core War Web
An open source web corewar

## Pre-requisites
* A functionnal Node.js environment
* Functionnal C++ compilation tools
* A working MongoDB database

## Setup
### Clone this repository
```
$> cd
$> git clone https://github.com/MIT-Niceti/core-war-web.git
$> cd core-war-web
```

### Server configuration file
```
$> cd config/
$> cp app.config.json.example app.config.json
$> cd ..
```
Then replace the appropriate fields for your environment in `config/app.config.json`

### Install internal/external project dependancies
```
$> npm install
```

## Use
### Launch the server
```
$> npm start
Http server listening on port 8080
```

### Web service access
Take a look again in `config/app.config.json`, and note the value of the fields `http.hostname` and `http.port`.
Open your web browser, and enter an address following this syntax:  
Add the value of `http.hostname`, plus the colon character `:`, then the value of `http.port`, and press Enter !
