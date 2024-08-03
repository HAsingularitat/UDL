#ifndef ROLES_H
#define ROLES_H

#include <Arduino.h>

enum RoleType {
    KING,
    QUEEN,
    BISHOP,
    KNIGHT_1,
    KNIGHT_2,
    PAWN,
    ROOK
};

class RoleProperties {
public:
    RoleType type;
    String description;
    bool canInitiateCommunication;
    bool canReceiveCommands;
    bool canChangeRoles;
    bool canSyncTime;
    bool canInitiateSleep;
    bool canRequestSpecificData;

    RoleProperties(RoleType type) {
        this->type = type;
        initializeProperties();
    }

    void initializeProperties() {
        switch (type) {
            case KING:
                description = "Control total, puede modificar cualquier aspecto de la red";
                canInitiateCommunication = true;
                canReceiveCommands = true;
                canChangeRoles = true;
                canSyncTime = true;
                canInitiateSleep = true;
                canRequestSpecificData = true;
                break;
            case QUEEN:
                description = "Coordina y sincroniza, maneja peticiones de datos y actualizaciones de tiempo";
                canInitiateCommunication = true;
                canReceiveCommands = true;
                canChangeRoles = false;
                canSyncTime = true;
                canInitiateSleep = true;
                canRequestSpecificData = true;
                break;
            case BISHOP:
                description = "Maneja sensores críticos y no puede convertirse en reina";
                canInitiateCommunication = false;
                canReceiveCommands = true;
                canChangeRoles = false;
                canSyncTime = true;
                canInitiateSleep = false;
                canRequestSpecificData = false;
                break;
            case KNIGHT_1:
                description = "Sensores importantes con alta disponibilidad, puede convertirse en reina";
                canInitiateCommunication = true;
                canReceiveCommands = true;
                canChangeRoles = true;
                canSyncTime = true;
                canInitiateSleep = true;
                canRequestSpecificData = true;
                break;
            case KNIGHT_2:
                description = "Sensores importantes con baja disponibilidad, pero puede convertirse en reina";
                canInitiateCommunication = true;
                canReceiveCommands = true;
                canChangeRoles = true;
                canSyncTime = true;
                canInitiateSleep = true;
                canRequestSpecificData = true;
                break;
            case PAWN:
                description = "Sensores no indispensables, prioridad alta para convertirse en reina";
                canInitiateCommunication = false;
                canReceiveCommands = true;
                canChangeRoles = true;
                canSyncTime = false;
                canInitiateSleep = false;
                canRequestSpecificData = false;
                break;
            case ROOK:
                description = "Encargado de conexiones, detalles por definir";
                canInitiateCommunication = true;
                canReceiveCommands = true;
                canChangeRoles = false;
                canSyncTime = false;
                canInitiateSleep = false;
                canRequestSpecificData = false;
                break;
        }
    }
};

#endif
