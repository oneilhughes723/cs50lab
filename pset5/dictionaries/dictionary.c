  // Iterate through the characters of string
    while ((c = *word++))
    {
        // Calculate (hash * 33) + c
        hash = ((hash << 5) + hash) + tolower(c);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //opens file and returns error if unable to open
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        printf("Error");
        unload();
        return false;
    }
    else
    {
        char word[LENGTH + 1];
        //scans the words in the file until the EOF has been reached and copies that word into a new node with a pointer to NULL
        while (fscanf(f, "%s", word) != EOF)
        {
            // hash word
            unsigned int hashval = hash(word);
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                printf("Unable to allocate memory for new node");
                return false;
            }
            strcpy(n->word, word);
            n->next = table[hashval];
            table[hashval] = n;
            word_count++;
        }
    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (table[i] != NULL)
        {
            cursor = cursor->next;
            free(table[i]);
            table[i] = cursor;
        }
        count++;
    }
    if (count == N)
    {
        return true;
    }
    return false;
}
