# 🐚 Minishell

Bienvenue dans **Minishell** ! Une implémentation minimaliste de shell Linux. Ce projet vise à fournir un environnement shell simple mais fonctionnel.

## ✨ Fonctionnalités

- Exécution de commandes de base via des fork et exec
- Redirection d'entrée/sortie avec `<`, `>`, `>>` et heredoc `<<`
- Pipes `|`
- Gestion des variables d'environnement
- Commandes intégrées comme `cd`, `exit`, `echo`, `env`, `export`, `pwd`, `unset`
- Gestion des signaux `Ctrl-C`, `Ctrl-D` et `Ctrl-\`
- Gestion des erreurs et des retours de commandes

## ⚠️ Attention

Ce projet a été réalisé a deux dans le cadre de la formation de l'école 42. Il peut contenir des bugs et des failles de sécurité. Et surtout si vous êtes étudiant de 42, n'oubliez pas que copier n'est pas autorisé, soyez responsable de votre travail. Bonne chance !

## 🚀 Installation

1. Clonez le dépôt :
    ```sh
    git clone https://github.com/Rockmard/minisHELL.git
    ```

2. Compilez le projet :
	```sh
	cd minishell
	make
	```

## 🛠️ Utilisation

1. Lancez le shell :
	```sh
	./minishell
	```
