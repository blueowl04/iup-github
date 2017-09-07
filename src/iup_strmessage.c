/** \file
 * \brief String Utilities
 *
 * See Copyright Notice in "iup.h"
 */

 
#include <string.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <limits.h>  
#include <stdarg.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_strmessage.h"
#include "iup_table.h"
#include "iup_register.h"
#include "iup_l10n.h"


static void iStrMessageRegisterInternal(void);

static Itable *istrmessage_table = NULL;   /* the message hash table indexed by the name string */

void iupStrMessageInit(void)
{
  istrmessage_table = iupTableCreate(IUPTABLE_STRINGINDEXED);

  iStrMessageRegisterInternal();
}

void iupStrMessageFinish(void)
{
  iupTableDestroy(istrmessage_table);
  istrmessage_table = NULL;
}

char* IupGetLanguageString(const char* name)
{
  char* value;
  if (!name) return NULL;
  value = (char*)iupTableGet(istrmessage_table, name);
  if (!value)
    return (char*)name;
  return value;
}

void IupSetLanguageString(const char* name, const char* str)
{
  iupTableSet(istrmessage_table, name, (char*)str, IUPTABLE_POINTER);
}

void IupStoreLanguageString(const char* name, const char* str)
{
  iupTableSet(istrmessage_table, name, (char*)str, IUPTABLE_STRING);
}

void IupSetLanguagePack(Ihandle* ih)
{
  if (!ih)
    iupTableClear(istrmessage_table);
  else
  {
    char *name, *value;

    name = iupTableFirst(ih->attrib);
    while (name)
    {
      value = (char*)iupTableGetCurr(ih->attrib);

      if (iupTableGetCurrType(ih->attrib)==IUPTABLE_STRING)
        iupTableSet(istrmessage_table, name, value, IUPTABLE_STRING);
      else
        iupTableSet(istrmessage_table, name, value, IUPTABLE_POINTER);

      name = iupTableNext(ih->attrib);
    }
  }
}

void IupSetLanguage(const char *language)
{
  IupStoreGlobal("LANGUAGE", language);
}

char *IupGetLanguage(void)
{
  return IupGetGlobal("LANGUAGE");
}


/**********************************************************************************/

typedef struct _IstdMessage
{
  const char* name;
  const char* lng_str;
} IstdMessage;

static IstdMessage iStdMessages[] =
{
  { "IUP_ERROR", "Error!" },
  { "IUP_ATTENTION", "Attention!" },
  { "IUP_YES", "Yes" },
  { "IUP_NO", "No" },
  { "IUP_INVALIDDIR", "Invalid directory." },
  { "IUP_FILEISDIR", "The selected name is a directory." },
  { "IUP_FILENOTEXIST", "File does not exist." },
  { "IUP_FILEOVERWRITE", "Overwrite existing file?" },
  { "IUP_CREATEFOLDER", "Create Folder" },
  { "IUP_NAMENEWFOLDER", "Name of the new folder:" },
  { "IUP_SAVEAS", "Save As" },
  { "IUP_OPEN", "Open" },
  { "IUP_SELECTDIR", "Select Directory" },
  { "IUP_OK", "OK" },
  { "IUP_CANCEL", "Cancel" },
  { "IUP_RETRY", "Retry" },
  { "IUP_APPLY", "Apply" },
  { "IUP_RESET", "Reset" },
  { "IUP_GETCOLOR", "Color Selection" },
  { "IUP_HELP", "Help" },
  { "IUP_RED", "&Red:" },
  { "IUP_GREEN", "&Green:" },
  { "IUP_BLUE", "&Blue:" },
  { "IUP_HUE", "&Hue:" },
  { "IUP_SATURATION", "&Saturation:" },
  { "IUP_INTENSITY", "&Intensity:" },
  { "IUP_OPACITY", "&Opacity:" },
  { "IUP_PALETTE", "&Palette:" },
  { "IUP_TRUE", "True" },
  { "IUP_FALSE", "False" },
  { "IUP_FAMILY", "Family:" },
  { "IUP_STYLE", "Style:" },
  { "IUP_SIZE", "Size:" },
  { "IUP_SAMPLE", "Sample:" },
  { "IUP_ERRORFILEOPEN", "Failed to open file." },
  { "IUP_ERRORFILESAVE", "Failed to save file." },
  { "IUP_LUAERROR", "Lua Error" },
  { "IUP_CONTINUE", "Continue" },
  { "IUP_COPYTOCLIPBOARD", "Copy text to clipboard." },
  { "IUP_COPY", "Copy" },
  { "IUP_EXIT", "Exit" },
  { NULL, NULL }
};

static void iStrMessageRegisterInternal(void)
{
  IstdMessage* messages = iStdMessages;
  while (messages->name)
  {
    IupSetLanguageString(messages->name, messages->lng_str);
    messages++;
  }
}

void iupStrMessageUpdateLanguage(const char* language)
{
  /* called after the global attribute is changed */

  if (iupStrEqualNoCase(language, "ENGLISH"))
    iStrMessageRegisterInternal();
  else
    iupSetLangStrings(language, IupGetInt(NULL, "UTF8MODE"), "stdmessages");

  iupRegisterUpdateClasses();
}
