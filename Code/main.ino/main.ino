#include <Arduino.h>
#include "Config.h"  // Incluir configuración general

// Incluir el archivo de rol correspondiente
#ifdef ROLE_KING
#include "KingRole.h"
KingRole role;
#endif

#ifdef ROLE_QUEEN
#include "QueenRole.h"
QueenRole role;
#endif

#ifdef ROLE_PAWN
#include "PawnRole.h"
PawnRole role;
#endif

void setup() {
    // Inicializar el rol
    role.setup();
}

void loop() {
    // Ejecutar la lógica específica del rol
    role.loop();
}
