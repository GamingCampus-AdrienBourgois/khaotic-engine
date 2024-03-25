#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

// Structure pour repr�senter un message du chat
struct Message {
    std::string sender; // Exp�diteur du message
    std::string recipient; // Destinataire du message (peut �tre vide si c'est un message public)
    std::string content; // Contenu du message
};

#endif // MESSAGE_H

