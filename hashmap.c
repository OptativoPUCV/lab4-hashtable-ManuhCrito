#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap* mapa, char* clave, void* valor)
{
  int pos = hash(clave, mapa->capacity);
  if (mapa->buckets[pos] == NULL)
  {
    mapa->buckets[pos] = createPair(clave, valor);
    mapa->size++;
    mapa->current = pos;
  }
  else
  {
    while (mapa->buckets[pos] != NULL)
      {
        pos++;
        if (pos == mapa->capacity) pos = 0;
      }
    mapa->buckets[pos] = createPair(clave, valor);
    mapa->size++;
    mapa->current = pos;
  }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity)
{
  HashMap* mapa = (HashMap*)malloc(sizeof(HashMap));
  mapa->buckets = (Pair**)calloc(capacity, sizeof(Pair*));
  mapa->size = 0;
  mapa->capacity = capacity;
  mapa->current = -1;
    return mapa;
}

void eraseMap(HashMap * map,  char * key)
{    
  int pos = hash(key, map->capacity);
  while (map->buckets[pos] != NULL && map->buckets[pos]->key != NULL)
    {
      if (is_equal(map->buckets[pos]->key, key) == 1)
      {
        map->buckets[pos]->key = NULL;
        map->size--;
        return;
      }
      pos = (pos + 1) % map->capacity;
    }
}

Pair * searchMap(HashMap * map,  char * key)
{   
  if (map == NULL || key == NULL) return NULL;

  int pos = hash(key, map->capacity);
  while (map->buckets[pos] != NULL)
    {
      if (is_equal(map->buckets[pos]->key, key) == 1)
      {
        map->current = pos;
        return map->buckets[pos];
      }
      pos++;
    }
  return NULL;
}

Pair * firstMap(HashMap * map)
{
  if (map == NULL) return NULL;

  for (int i = 0 ; i < map->capacity ; i++)
    {
      if (map->buckets[i] != NULL && map->buckets[i]->key != NULL)
      {
        map->current = i;
        return map->buckets[i];
      }
    }
  return NULL;
}

Pair * nextMap(HashMap * map)
{
  if (map == NULL) return NULL;
  if (map->current == -1) return NULL;

  for (int i = map->current + 1 ; i < map->capacity ; i++)
    {
      if (map->buckets[i] != NULL)
      {
        map->current = i;
        return map->buckets[i];
      }
    }
  return NULL;
}