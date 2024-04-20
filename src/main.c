#include <popt.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

int main(int argc, const char * argv[])
{
	/* Parse command-line arguments */
	int brightness = -1;
	struct poptOption optionsTable[] = {
		{"brightness", 'b', POPT_ARG_INT, &brightness, 0, "Set brightness value", "BRIGHTNESS"},
		POPT_AUTOHELP
		{NULL, '\0', POPT_ARG_NONE, NULL, 0, NULL, NULL}
	};
	poptContext pContext = poptGetContext(PACKAGE_NAME, argc, argv, optionsTable,
										  POPT_CONTEXT_POSIXMEHARDER);
	int poptResult = 0;
	if((poptResult = poptGetNextOpt(pContext)) < -1)
	{
		fprintf(stderr, "%s: %s\n",
				poptBadOption(pContext, POPT_BADOPTION_NOALIAS),
				poptStrerror(poptResult));
		poptFreeContext(pContext);
		return 1;
	}
	poptFreeContext(pContext);

	return 0;
}
