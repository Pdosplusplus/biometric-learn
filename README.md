# LEARN BIOMETRIC 

In this manual we go simulate the proccess the one system of biometric

* The first step will be to create a simple system client-server that communicate with the protocol XML-RPC.

* The second step will be to create a system client-server that simulate the Manage all processes of a system biometric with the protocol of communication XML-RPC.


# First Module: System client-server that communicate with the protocol XML-RPC.

# 1. Install dependencies to work with XML-RPC

We go working with the linux distrubution Canaima that is a derivate of Debian Jessie.

## 1.1 Install Dependecies to Client

* Client common-libs:

Execute:

```bash
$ sudo apt install libusb-0.1-4 libusb-1.0-0 udev fxload
```
			
Client interface:

Execute:
			
```bash
$ sudo apt install libusb-0.1-4 libusb-1.0-0 udev fxload libjpeg62-turbo libxmlrpc-c++8 libxmlrpc-core-c3 libcurl3 libcurl3-gnutls libc6 openssl curl ca-certificates zenity
```

## 1.2 Install Dependencies to Server

Execute:

```bash
$ sudo apt install libxmlrpc-c++8-dev libxmlrpc-core-c3 libxmlrpc-core-c3-dev libcurl3-gnutls libc6 openssl apache2 apache2-mpm-prefork cron curl libcurl4-gnutls-dev g++ libjpeg-dev libcrypto++-dev libssl-dev libpqxx-dev
```

And active the mod cgi

```bash
$ a2enmod cgi
```

and restart apache

```bash
$ sudo service apache2 restart
```
## 2. Create the client

### 2.1 Create a directory to work:

```bash
$ mkdir client && cd client
```

### 2.2 Create a Header file the name ```client.h``` 

> This file contains all libraries of ```C++``` that we need to work 

With the following content:

```bash
#ifndef _Client_H_
#define _Client_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <XmlRpcCpp.h>
#include <iostream>
#include <algorithm>

#define NAME       "XML-RPC Guide C++ Client"
#define VERSION    "0.1"

#endif
```

### 2.3 Create the logic of the client


Create a file ```client.cpp``` with the following content:


```c++
#include "client.h"

using namespace std;

string url = "";
   
string archivo_config(string config_url_service)
{
	string url = "";
	string line;
	ifstream myfile( config_url_service.c_str() );
	if (myfile)
	{
		while (getline( myfile, line ))
		{
			line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
			if (strcmp(line.c_str(), "") != 0)
			{
                printf("\nArchivo leído\n");
				url = line;
			}
		}
		myfile.close();
	}

	if(strcmp(url.c_str(), "") == 0)
	{
		ifstream myfile_default( "config/default" );
		if (myfile_default)
		{
			while (getline( myfile_default, line ))
			{
				line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
				if (strcmp(line.c_str(), "") != 0)
				{
                    printf("\nArchivo leído default");
					url = line;
				}
			}
			myfile.close();
		}
	}

    printf("\nurl %s\n",url.c_str());
	return url;
}

int sumAndDifferen(int opp_1,int opp_2, double opp_3){

	XmlRpcClient::Initialize(NAME, VERSION);

    try {
        XmlRpcValue param_array = XmlRpcValue::makeArray();
        
        param_array.arrayAppendItem(XmlRpcValue::makeInt(opp_1));
        param_array.arrayAppendItem(XmlRpcValue::makeInt(opp_2));
        param_array.arrayAppendItem(XmlRpcValue::makeDouble(opp_3));
        
        string SERVER_URL = url.c_str();
		XmlRpcClient server (SERVER_URL);
        
        XmlRpcValue result = server.call("sample.sumAndDifferen", param_array);
        
        XmlRpcValue::int32 sum = result.structGetValue("sum").getInt();
        XmlRpcValue::int32 difference = result.structGetValue("difference").getInt();
        double doble = result.structGetValue("doble").getDouble();
        
        XmlRpcClient::Terminate();
        
        cout << "Sum " << sum << " difference " << difference << " doble " << doble << endl;
        
    } catch (XmlRpcFault& fault) {
		cerr << ": XML-RPC fault #" << fault.getFaultCode() << ": " << fault.getFaultString() << endl;
        XmlRpcClient::Terminate();
        return 0;
	}
}
  
int msj(string sms){

	XmlRpcClient::Initialize(NAME, VERSION);

    try {

        XmlRpcValue param_array = XmlRpcValue::makeArray();
        
        param_array.arrayAppendItem(XmlRpcValue::makeString(sms));
        
        string SERVER_URL = url.c_str();
		XmlRpcClient server (SERVER_URL);
        
        XmlRpcValue result = server.call("sample.msj", param_array);
        
        string message = result.structGetValue("message").getString().c_str();
        
        XmlRpcClient::Terminate();
        
        cout << "message " << message.c_str() << endl;
        
    } catch (XmlRpcFault& fault) {
		cerr << ": XML-RPC fault #" << fault.getFaultCode() << ": " << fault.getFaultString() << endl;
        XmlRpcClient::Terminate();
        return 0;
	}
		
}

int main(int argc, char *argv[]){

	int option = atof(argv[1]);
    int opp_1 = atoi(argv[2]);
    int opp_2 = atoi(argv[3]);
    double opp_3 = atof(argv[4]);
    
    string sms = "LearnBiometric";

	string config = "config/config";
	url = archivo_config(config);

    switch (option) {

		case 1:
			sumAndDifferen(opp_1, opp_2, opp_3);
		break;

		case 2:
			msj(sms);
		break;

		default:
		  cout<<"Error, bad input, quitting\n";
		break;
	
	}

}
```

Now I will explain step by step the copied code

```c
#include "client.h"
```

In this line include all libraries that we need to work, that are in the file that we created before

```c++
string archivo_config(string config_url_service)
```

archivo_config is a function receive a string as parameter

This function does two things: 

* Verify that rute the file pass for parameter exist.
* Return in a variable the content the file.


#### Now we will create this file:

* Create a directory ```config```

```bash
$ mkdir config 
```

* Create a file ```config``` with the following content:

```bash
http://localhost/cgi-bin/server_pruebas/server.cgi
```

That file content the url the server,  to which we will do petitions

In this case the url is local.


* Create a file ```default``` with the following content:

```bash
http://localhost/cgi-bin/server.cgi
```

The same that the file config.


#### We continue with the explanation of the code

```c++
void sumAndDifferen(int opp_1,int opp_2, double opp_3)
```

* sumAndDifferen is a function that recieve 3 parameters, 2 int and 1 double


```c++
XmlRpcClient::Initialize(NAME, VERSION);
``` 

With this sentence initialize a client

```c++
try {
    XmlRpcValue param_array = XmlRpcValue::makeArray();
```

We created a array to pass to the server and opened a block try catch to capture a possible error.


```c++
param_array.arrayAppendItem(XmlRpcValue::makeInt(opp_1));
param_array.arrayAppendItem(XmlRpcValue::makeInt(opp_2));
param_array.arrayAppendItem(XmlRpcValue::makeDouble(opp_3));
```

We added to the array, the 3 values passed for parameters

```c++
string SERVER_URL = url.c_str();
```

Save in a variable the url the file config

```c++
XmlRpcClient server (SERVER_URL);
```

Initialize connect with the server.

```c++
XmlRpcValue result = server.call("sample.sumAndDifferen", param_array);
```

With ```server.call``` we called the function that is in the server and the pass the array with the data and in the variable ```result```  saved the result of the call.

```c++
XmlRpcValue::int32 sum = result.structGetValue("sum").getInt();
XmlRpcValue::int32 difference = result.structGetValue("difference").getInt();
double doble = result.structGetValue("doble").getDouble();
```

In this code we saved the data that the server returns us in variables

Accessing to the date with the object ```result``` and the funcion ```strucGetValue```


```c++
 XmlRpcClient::Terminate();
```

With this we closed the client of RPC

```c++
cout << "Sum " << sum << " difference " << difference << " doble " << doble << endl;  
```

Print the result the server returned us

```c++
} catch (XmlRpcFault& fault) {
	cerr << ": XML-RPC fault #" << fault.getFaultCode() << ": " << fault.getFaultString() << endl;
    XmlRpcClient::Terminate();
    return 0;
}
```

Function to capture a possible error.


```c++
void msj(string sms){
```

This function is the same logic that sumAndDifferen, what change is  we passed 1 string instead of integers

```c++
int main(int argc, char *argv[]){

	int option = atof(argv[1]);
    int opp_1 = atoi(argv[2]);
    int opp_2 = atoi(argv[3]);
    double opp_3 = atof(argv[4]);
```


In this code we saved the arguments passed by the user


```c++
string sms = "LearnBiometric";

switch (option) {

	case 1:
		sumAndDifferen(opp_1, opp_2, opp_3);
	break;

	case 2:
		msj(sms);
	break;

	default:
	  cout<<"Error, bad input, quitting\n";
	break;

}
```

In this code we declared a struct control to to analyze the options passed by the user.

* If the user passed 1, we will execute the function ```sumAndDifferen```

* If the user passed 2, we will execute the function ```msj```

* If not is 1 or 2 print a error. This option not exist.

And we have already created our client


#### Now copile the client

Created a file ```compilar.sh``` with the instruction to compile that are the nexts:

```bash
#!/bin/sh

CC=gcc
CXX=g++
SRCS=client.cpp
CLIENT_CFLAGS=`xmlrpc-c-config c++ libwww-client --cflags`
CLIENT_LIBS=`xmlrpc-c-config c++ libwww-client --libs`
OBJS=client.o

g++ $CLIENT_CFLAGS -o $OBJS $SRCS $CLIENT_LIBS
```

##### And now execute

```bash
$ sh compilar.sh
```

## 3. Create the server

### 3.1 Create a directory to work:

```bash
$ mkdir server && cd server
```

### 3.2 Create a Header file the name ```server.h``` 

> This file contains all libraries of ```C++``` that we need to work 

With the following content:

```bash
#ifndef _Server_H_
#define _Server_H_

#include <xmlrpc.h>
#include <xmlrpc_cgi.h>
#include <XmlRpcCpp.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>

#define NAME       "XML-RPC Guide C++ Client"
#define VERSION    "0.1"

#endif
```

### 2.3 Create the logic of the server

Create a file ```server.cpp``` with the following content:

```c++
#include "server.h"

using namespace std;

xmlrpc_value *

sumAndDifference (xmlrpc_env *env, xmlrpc_value *param_array, void *user_data)
{
    if(user_data != NULL)
        user_data = NULL;
    
    xmlrpc_value * value;
    xmlrpc_int32 x, y; 
    xmlrpc_double doble;
    
    xmlrpc_array_read_item(env, param_array, 0, &value);
    xmlrpc_read_int(env, value, &x);
    xmlrpc_DECREF(value);
    
    xmlrpc_array_read_item(env, param_array, 1, &value);
    xmlrpc_read_int(env, value, &y);
    xmlrpc_DECREF(value);
    
    xmlrpc_array_read_item(env, param_array, 2, &value);
    xmlrpc_read_double(env, value, &doble);
    xmlrpc_DECREF(value);

    if(y != 0)
    {
        doble = ((double)x)/((double)y);
    }

    // Return our result.
    return xmlrpc_build_value(env, "{s:i,s:i,s:d}",
	                      "sum", x + y,
	                      "difference", x - y,
                          "doble", doble);
}

xmlrpc_value *

msj (xmlrpc_env *env, xmlrpc_value *param_array, void *user_data)
{
    if(user_data != NULL)
        user_data = NULL;

    xmlrpc_value * value;    
    const char * cadena;
    
    xmlrpc_array_read_item(env, param_array, 0, &value);
	xmlrpc_read_string(env, value, &cadena);
	xmlrpc_DECREF(value);
   
    // Return our result.
    return xmlrpc_build_value(env, "{s:s}",
	                      "message", cadena);
}

/**
 * @brief Main
 * @return Devuelve el estado del Main
 */

int main()
{
	/* Establece las bibliotecas CGI. */
	xmlrpc_cgi_init(XMLRPC_CGI_NO_FLAGS);

	/* Establece el tamaño límite del XMLRPC */
	xmlrpc_limit_set(XMLRPC_XML_SIZE_LIMIT_ID, 102400000);//5e6);

	xmlrpc_cgi_add_method_w_doc("sample.sumAndDifferen",
		                &sumAndDifference, NULL,
		                "S:ii", "Add and subtract two integers.");

	xmlrpc_cgi_add_method_w_doc("sample.msj",
		                &msj, NULL,
		                "S:ii", "Mensajito");

	/* Llama al método apropiado. */
	xmlrpc_cgi_process_call();

	/* Limpia nuestra biblioteca CGI. */
	xmlrpc_cgi_cleanup();

}
```

#### Now I will explain step by step the copied code


```c++
sumAndDifference (xmlrpc_env *env, xmlrpc_value *param_array, void *user_data){
```

This function calculates a sum, a subtraction and a division
And @return  The Struct result.

Recieve 3 parameters:

 * @param env Variable XMLRPC de ambiente
 * @param param_array Array que viene del cliente
 * @param user_data Variables que vengan del usuario

```c++
xmlrpc_value * value;
xmlrpc_int32 x, y;
xmlrpc_double doble;
```

We declare the variables that we will use to the save the data And then use them in operations


```c++
xmlrpc_array_read_item(env, param_array, 0, &value);
```

this function read the item of array passed by the user in the position 0


```c++
xmlrpc_read_int(env, value, &x);
```

We assign the value to the variable ```x```

```c++
xmlrpc_DECREF(value);
```

We release the memory


#### This repeat in the following lines


```c++
return xmlrpc_build_value(env, "{s:i,s:i,s:d}",
	                      "sum", x + y,
	                      "difference", x - y,
                          "doble", doble);                 
```

With this function return the information to client need


with ```xmlrpc_build_value``` we build a file struct (table hash)

and return the data to client in ```"{s:i,s:i,s:d}"``` this is the struc the message check that key ```sum``` is string and ```x + y``` is integer the same for the following lines.



```c++
msj (xmlrpc_env *env, xmlrpc_value *param_array, void *user_data)
```

This function is the same that sumAndDifference the only thing that changes is that it returns a string

* check:

```c++
return xmlrpc_build_value(env, "{s:s}",
	                      "message", cadena);
```


```c++
xmlrpc_cgi_init(XMLRPC_CGI_NO_FLAGS);
```

 This function Sets the libraries CGI. 

```c++
xmlrpc_limit_set(XMLRPC_XML_SIZE_LIMIT_ID, 102400000);
```

This function sets the size limit of the XMLRPC


```c++
xmlrpc_cgi_add_method_w_doc("sample.sumAndDifferen",
		                &sumAndDifference, NULL,
		                "S:ii", "Add and subtract two integers.");
```


This function allow to add a function at server and after  the client can consult


Receives 5 parameters:


* sample.<name the function>

* &<Name of the function that contains the logic>

* NULL: Extra parameters.

* S:ii = Struc that return.

* A description the function.


```c++
xmlrpc_cgi_process_call();
```

This function call the method appropriate

```c++
xmlrpc_cgi_cleanup();
```

This function clean the libraries of CGI.


### And we have already created our server


#### Now copile the server

Created a file ```compilar.sh``` with the instruction to compile that are the nexts:

```bash
#!/bin/sh

CLIENT_CFLAGS=`xmlrpc-c-config c++ libwww-client --cflags`
CLIENT_LIBS=`xmlrpc-c-config c++ libwww-client --libs`
CGI_CFLAGS=`xmlrpc-c-config cgi-server --cflags`
CGI_LIBS=`xmlrpc-c-config cgi-server --libs`

g++ $CGI_CFLAGS $CLIENT_CFLAGS \
  server.cpp -o \
  server.cgi \
  $CGI_LIBS $CLIENT_LIBS

mkdir -p /usr/lib/cgi-bin/server_pruebas/
cp server.cgi /usr/lib/cgi-bin/server_pruebas/

chmod 740 /usr/lib/cgi-bin/ -R
chown www-data:www-data /usr/lib/cgi-bin/ -R
```

> Before compiling the code we need the binary of ```server.cgi```

##### And now execute 

```bash
$ sudo sh compilar.sh
```

> To check the server run ok. In your browser check the url of the server:

http://localhost/cgi-bin/server_pruebas/server.cgi

#### And you should get this message:

> 405 Method Not Allowed An error occurred processing your request. XML-RPC Fault #-500: Expected HTTP method POST


#### Ok ok, Time to test the application

##### Go to directory ```client``` and execute the file ```client.o```

Execute:

```bash
$ ./client.o 1 1 1 1
```

##### And you should get this message:

```bash
Archivo leído

url http://localhost/cgi-bin/server_pruebas/server.cgi
Sum 2 difference 0 doble 1
```

##### Now execute again but with the first parameter = 2

```bash
$ ./client.o 2 1 1 1
```

##### And you should get this message:

```bash
Archivo leído

url http://localhost/cgi-bin/server_pruebas/server.cgi
message LearnBiometric
```

### Now play with that.


