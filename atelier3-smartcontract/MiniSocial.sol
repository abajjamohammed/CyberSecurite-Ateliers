// SPDX-License-Identifier: MIT
pragma solidity ^0.8.26;

/**
 * @title MiniSocial
 * @dev Smart Contract d'un mini réseau social décentralisé
 */
contract MiniSocial {

    // 1. Déclaration de la structure Post (Instruction 1)
    struct Post {
        string message;
        address author;
    }

    // 2. Tableau dynamique pour stocker tous les messages (Instruction 2)
    Post[] public posts;

    // Événement pour notifier les DApps lorsqu'un message est publié (Vu en cours slide 20)
    event PostPublished(uint256 indexed id, address indexed author, string message);

    // 3. Fonction de publication d'un message (Instruction 3)
    function publishPost(string memory _message) public {
        // Sécurité : Vérifier que le message n'est pas vide (require vu en cours slide 19)
        require(bytes(_message).length > 0, "Le message ne peut pas etre vide !");

        // Création et ajout du nouveau post avec msg.sender (l'adresse de l'utilisateur)
        posts.push(Post({
            message: _message,
            author: msg.sender
        }));

        // Émission de l'événement
        emit PostPublished(posts.length - 1, msg.sender, _message);
    }

    // 4. Fonction de consultation d'un post par son index (Instruction 4)
    function getPost(uint256 index) public view returns (string memory, address) {
        require(index < posts.length, "Index invalide : ce post n'existe pas !");
        Post memory p = posts[index];
        return (p.message, p.author);
    }

    // 5. Fonction pour récupérer le nombre total de messages (Instruction 5)
    function getTotalPosts() public view returns (uint256) {
        return posts.length;
    }
}