// output se debería comer algunas de las funcionalidades de Command!
// por ahora tengo una clase pero debería haber Server y ClientOuput
#ifndef OUTPUT_H
#define OUTPUT_H

#include "common_command.h"

class Output {
public:
// para el refactor la info del equipment la va a tener
// privada, y directamente las seria y deserializaciones
// se van a alocar en el output, no hay necesidad de tener
// el intermediario Command...
// o sí necesito el Command? de alguna forma el server
// tiene que mandar el mensaje, ah, puede construir el output
// enviarselo al client serializado por el protocol y que el
// server deserialice y ejecute ;)
    static void output_equipment(
        Command equipment);
};

#endif
