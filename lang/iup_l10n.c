#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "iup.h"
#include "iup_str.h"
#include "iup_l10n.h"


typedef struct {
  const char *var;   /* Variable */
  const char *text;  /* Localized text */
} iLocalString;

typedef struct {
  const char *name;
  iLocalString *table;
} iLangMap;

/* Generated tables with translated strings are included here */
#include "iup_l10n_gen.h"

static iLocalString *iFindTable(const char *lang, int utf8, const char *group)
{
  char str[255];
  char *lang_upper;
  int i;

  lang_upper = iupStrDup(lang);
  iupStrUpper(lang_upper, lang);
  sprintf(str, "l10n_%s_%s_%s", lang_upper, utf8 ? "utf_8" : "latin1", group);
  free(lang_upper);

  for (i = 0; LANGS[i].name; i++) {
    if (strcmp(LANGS[i].name, str) == 0)
      return LANGS[i].table;
  }
  return NULL;
}

void iupSetLangStrings(const char *lang, int utf8, const char *group)
{
  iLocalString *table = iFindTable(lang, utf8, group);

  if (!table) return;

  for (int i = 0; table[i].var; i++) {
    IupSetLanguageString(table[i].var, table[i].text);
  }
}

