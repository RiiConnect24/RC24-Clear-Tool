#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <ogcsys.h>

#include "tools.h"

extern void __exception_setreload(int);

int main(int argc, char *argv[])
{
	__exception_setreload(10);

	int i, ret;

	clear();

	PAD_Init();
	WPAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);

	ret = ahbprot_menu();
	if (ret < 0)
	{
		ret = ios_selectionmenu(80);
		if (ret > 0)
		{
			printf("\t- Reloading to IOS%d... ", ret);
			WPAD_Shutdown();
			IOS_ReloadIOS(ret);
			sleep(2);
			PAD_Init();
			WPAD_Init();
			WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
			printf("done.\n\n");
		}
		else if (ret == 0)
		{
			printf("\t- Proceeding without IOS reload...\n\n");
		}
		else
		{
			Reboot();
		}
	}

	clear();

	printf("Press +Up to delete Forecast Channel data.\n");
	printf("Press +Down to delete News Channel data.\n");
	printf("Press +Left to delete WiiConnect24 mailboxes.\n");
	printf("Press +Right to delete nwc24msg.cfg.\n");
	printf("Press A to delete SYSCONF.\n\n");
	printf("Press HOME to exit.\n");

	/* Initialize NAND FS */
	ISFS_Initialize();

	/* Do our stuff */
	char path[ISFS_MAXPATH];

	char *filenames[4];
	int size;

	while (true)
	{
		u32 pressed = DetectInput(DI_BUTTONS_DOWN);

		if (pressed & WPAD_BUTTON_UP)
		{
			printf("This will delete the file containing Forecast Channel data that\n");
			printf("has been downloaded. This will not fix FORE000006.\n\n");

			printf("Deleting this file can resolve all of these errors:\n\n");

			printf("- Discontinued Message\n");
			printf("- FORE000001\n");
			printf("- FORE000005\n");
			printf("- FORE000099\n\n");

			usleep(5000000);

			printf("Are you sure you want to delete this file?\n\n");

			printf("Press the B Button to confirm.\n");
			printf("Press HOME or Start to exit.");

			filenames[0] = "/title/00010002/48414645/data/wc24dl.vff";
			filenames[1] = "/title/00010002/48414650/data/wc24dl.vff";
			filenames[2] = "/title/00010002/4841464a/data/wc24dl.vff";

			size = 3;

			break;
		}

		else if (pressed & WPAD_BUTTON_DOWN)
		{
			printf("This will delete the file containing News Channel data that\n");
			printf("has been downloaded. This will not fix NEWS000006.\n\n");

			printf("Deleting this file can resolve all of these errors:\n\n");

			printf("- Discontinued Message\n");
			printf("- NEWS000001\n");
			printf("- NEWS000003\n");
			printf("- NEWS000005\n");
			printf("- NEWS000099\n\n");

			usleep(5000000);

			printf("Are you sure you want to delete this file?\n\n");

			printf("Press the B Button to confirm.\n");
			printf("Press HOME or Start to exit.");

			filenames[0] = "/title/00010002/48414745/data/wc24dl.vff";
			filenames[1] = "/title/00010002/48414750/data/wc24dl.vff";
			filenames[2] = "/title/00010002/4841474a/data/wc24dl.vff";

			size = 3;

			break;
		}

		else if (pressed & WPAD_BUTTON_LEFT)
		{
			printf("This will delete your Wii's mailboxes containing incoming\n");
			printf("and outgoing mail. It will not delete your mail on the\n");
			printf("Wii Message Board. It can be good to clear this if you are\n");
			printf("having trouble sending/receiving mail, especially the latter.\n\n");

			printf("If you choose to delete this, when you go to the Wii Menu\n");
			printf("it will claim the Wii Message Board data is corrupted and\n");
			printf("has been repaired. This is normal.\n\n");

			usleep(5000000);

			printf("Are you sure you want to delete your mailboxes?\n\n");

			printf("Press the B Button to confirm.\n");
			printf("Press HOME or Start to exit.");

			filenames[0] = "/shared2/wc24/mbox/wc24recv.ctl";
			filenames[1] = "/shared2/wc24/mbox/wc24recv.mbx";
			filenames[2] = "/shared2/wc24/mbox/wc24send.ctl";
			filenames[3] = "/shared2/wc24/mbox/wc24send.mbx";

			size = 4;

			break;
		}

		else if (pressed & WPAD_BUTTON_RIGHT)
		{
			printf("This will delete your Wii's nwc24msg.cfg file that stores the URLs\n");
			printf("for Wii Mail and login credentials for the server. It can be good to\n");
			printf("delete this if you think your nwc24msg.cfg is messed up.\n\n");

			printf("If you choose to delete this, when you go to the Wii Menu,\n");
			printf("it will claim the Wii Message Board data is corrupted and\n");
			printf("has been repaired. This is normal.\n\n");

			usleep(5000000);

			printf("Are you sure you want to delete your nwc24msg.cfg?\n\n");

			printf("Press the B Button to confirm.\n");
			printf("Press HOME or Start to exit.");

			filenames[0] = "/shared2/wc24/nwc24msg.cbk";
			filenames[1] = "/shared2/wc24/nwc24msg.cfg";

			size = 2;

			break;
		}

		else if (pressed & WPAD_BUTTON_A)
		{
			printf("This will delete your Wii's SYSCONF file, which contains some crucial\n");
			printf("settings for your Wii. This will likely fix error NEWS000006.\n\n");

			printf("If you choose to delete this, your Wii will go into initial setup mode.\n");
			printf("Your mail on your Wii Message Board will also be deleted, so make sure to\n");
			printf("backup /title/00000001/00000002/data/cdb.vff on your NAND if you wish to\n");
			printf("keep your mail.\n\n");

			printf("Keep in mind that deleting your SYSCONF is safe.\n\n");

			usleep(5000000);

			printf("Are you sure you want to delete your SYSCONF?\n\n");

			printf("Press the B Button to confirm.\n");
			printf("Press HOME or Start to exit.");

			filenames[0] = "/shared2/sys/SYSCONF";

			size = 1;

			break;
		}

		else if (pressed & WPAD_BUTTON_HOME)
		{
			printf("Exiting...");
			Reboot();
		}
	}

	while (true)
	{
		u32 pressed = DetectInput(DI_BUTTONS_DOWN);

		if (pressed & WPAD_BUTTON_B)
		{
			clear();

			printf("Deleting files...\n\n");

			int j = 0;

			for (i = 0; i < size; i++)
			{
				snprintf(path, MAX_CHARACTERS(path), "%s", filenames[i]);

				ret = ISFS_Delete(path);
				if (ret < 0)
				{
					switch (ret)
					{
					case -1:
					case -102:
						printf("\n\tError: Permission denied!");
						break;
					case -2:
					case -105:
						printf("\n\tError: File exists!");
						break;
					case -4:
					case -101:
						printf("\n\tError: Invalid argument!");
						break;
					case -6:
					case -106:
						break;
					case -8:
					case -118:
						printf("\n\tError: Resource busy!");
						break;
					case -12:
					case -103:
					case -114:
						printf("\n\tError: NAND ECC failure!");
						break;
					case -22:
						printf("\n\tError: Memory allocation failed during request!");
						break;
					case -107:
					case -109:
						printf("\n\tError: Too many files open!");
						break;
					case -108:
						printf("\n\tError: Memory full!");
						break;
					case -110:
						printf("\n\tError: Path name is too long!");
						break;
					case -111:
						printf("\n\tError: File already open!");
						break;
					case -115:
						printf("\n\tError: Directory not empty!");
						break;
					case -116:
						printf("\n\tError: Max directory depth exceeded!");
						break;
					default:
						printf("\n\tFATAL / UNKNOWN ERROR!!!");
					}

					if (ret <= -119)
						break;
				}
				else
				{
					printf("%s deleted!\n", path);
					j += 1;
				}

				usleep(2000000); // 2 seconds
			}

			if (j == 0)
			{
				clear();

				printf("No files were found to delete.\n");

				usleep(2000000); // 2 seconds
			}
			else
			{
				printf("\n");
			}

			break;
		} else if ( pressed & WPAD_BUTTON_HOME ) {
			break;
		}
	}

	clear();

	printf("Done! Exiting...\n");

	/* Unmount NAND FS and exit */
	ISFS_Deinitialize();
	Reboot();

	return 0;
}
