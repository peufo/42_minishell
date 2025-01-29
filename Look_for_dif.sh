#!/bin/bash
#merci chatGPT (mais il faut modifier quelques trucs, car c'est insalubre la...)
# Fichiers de sortie
BASH_LOG="test_origin.log"
MINISHELL_LOG="test_minishell.log"
DIFF_LOG="differences.log"

# Liste des commandes à exécuter
COMMANDS=(
    "echo Hello, world!"
    "pwd"
    "ls -la"
    "cat /etc/os-release"
    "env"
    "whoami"
    "echo \$HOME"
    "unset PATH && ls"
)

# Nettoyage des fichiers précédents
> $BASH_LOG
> $MINISHELL_LOG
> $DIFF_LOG

# Exécuter les commandes avec Bash et enregistrer les résultats
echo "Running commands in Bash..."
for CMD in "${COMMANDS[@]}"; do
    echo "Command: $CMD" >> $BASH_LOG
    bash -c "$CMD" >> $BASH_LOG 2>&1
    echo "" >> $BASH_LOG
done

# Exécuter les commandes avec ./minishell et enregistrer les résultats
echo "Running commands in ./minishell..."
for CMD in "${COMMANDS[@]}"; do
    echo "Command: $CMD" >> $MINISHELL_LOG
    echo "$CMD" | ./minishell >> $MINISHELL_LOG 2>&1
    echo "" >> $MINISHELL_LOG
done

# Comparer les deux fichiers et enregistrer les différences
echo "Comparing results..."
diff -u $BASH_LOG $MINISHELL_LOG > $DIFF_LOG

# Résumé des résultats
echo "Execution complete."
echo "Results stored in:"
echo "  - Bash results: $BASH_LOG"
echo "  - Minishell results: $MINISHELL_LOG"
echo "  - Differences: $DIFF_LOG"
