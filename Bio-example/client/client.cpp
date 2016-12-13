#include "client.h"

using namespace std;

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

int main(int argc, char *argv[])
{
	int option = atof(argv[1]);
    int opp_1 = atoi(argv[2]);
    int opp_2 = atoi(argv[3]);
    double opp_3 = atof(argv[4]);
    

    string msj = "LearnBiometric";

    string url = "";
    string config = "config/config";
        
    url = archivo_config(config);
    
    if (option == 1) {

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

    } else {

    	XmlRpcClient::Initialize(NAME, VERSION);

	    try {

	        XmlRpcValue param_array = XmlRpcValue::makeArray();
	        
	        param_array.arrayAppendItem(XmlRpcValue::makeString(msj));
	        
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

    
}
