# Core War Web
A Node.js/C++ corewar http server

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
#### Default address
The default url address is `http://localhost:8080`

#### Custom address
Copy/paste the default address in your browser. Take a look in `config/app.config.json`, and use the value of the fields `http.hostname` and `http.port`, to respectively replace `localhost` and `8080`.
