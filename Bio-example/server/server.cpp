#include "server.h"

using namespace std;

/**
 * @brief Ejemplo de Suma y Diferencia
 * @param env Variable XMLRPC de ambiente
 * @param param_array Array que viene del cliente
 * @param user_data Variables que vengan del usuario
 * @return Devuelve el Struct resultante
 */
 
xmlrpc_value *

sumAndDifference (xmlrpc_env *env, xmlrpc_value *param_array, void *user_data)
{
    if(user_data != NULL)
        user_data = NULL;
    
    /*
	 * 
	 * Hay un Bug en el método xmlrpc_parse_value(). En vez de ese, deben usar el método xmlrpc_array_read_item().
	 * http://xmlrpc-c.sourceforge.net/doc/libxmlrpc.html#interpretingarray
	 *
	 * //Valor XMLRPC
	 * xmlrpc_value * value;
	 *
	 * //Variable unsigned char para Base64
	 * const unsigned char * cvalue;
	 * size_t long_val;
	 *
	 * //Variable para enteros (int)
	 * xmlrpc_int firstInt;
	 *
	 * //Variable String
	 * const char * char_value;
     * 
     * //Variable Double
     * xmlrpc_double doble;
	 *
	 * Para leer Base64: 
	 * 	xmlrpc_array_read_item(env, param_array, 0, &value);
	 * 	xmlrpc_read_base64(env, value, &long_val, &cvalue);
	 * 	xmlrpc_DECREF(value);
	 * 	free((void *)cvalue);
	 *
	 * Para leer Int:
	 *	xmlrpc_array_read_item(env, param_array, 1, &value);
	 *	xmlrpc_read_int(env, value, &firstInt);
	 *	xmlrpc_DECREF(value);
     * 
     * Para leer Double:
     *  xmlrpc_array_read_item(env, param_array, 2, &value);
     *  xmlrpc_read_double(env, value, &doble);
     *  xmlrpc_DECREF(value);
	 *
	 * Para leer String:
	 *	xmlrpc_array_read_item(env, param_array, 3, &value);
	 *	xmlrpc_read_string(env, value, &char_value);
	 *	xmlrpc_DECREF(value);
	 *	free((void *)char_value);
	 *
	 * Así estaba antes:
     * xmlrpc_parse_value(env, param_array, "(ii)", &x, &y);
     * Otro ejemplo
	 * xmlrpc_parse_value(env, param_array, "(ssssss6)", &firma_cliente, &login, &pass, &id_persona, &id_dedo, &mano, &buffer, &length, &id_proyecto);
	 *
	 */
    xmlrpc_value * value;
    xmlrpc_int32 x, y; //xmlrpc_int
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


/**
 * @brief Imprime un mensaje
 * @param env Variable XMLRPC de ambiente
 * @param param_array Array que viene del cliente
 * @param user_data Variables que vengan del usuario
 * @return Devuelve el Struct resultante
 */
 
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
	//free((void *)cadena);
   
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
