#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

// Structure pour représenter un message du chat
struct Message {
    std::string sender; // Expéditeur du message
    std::string recipient; // Destinataire du message (peut être vide si c'est un message public)
    std::string content; // Contenu du message
};

#endif // MESSAGE_H

