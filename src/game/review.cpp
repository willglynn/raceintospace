/*
    Copyright (C) 2005 Michael K. McCarty & Fritz Bronner

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
// Interplay's BUZZ ALDRIN's RACE into SPACE
//
// Formerly -=> LiftOff : Race to the Moon :: IBM version MCGA
// Copyright 1991 by Strategic Visions, Inc.
// Designed by Fritz Bronner
// Programmed by Michael K McCarty
//
// Review Main Files

#include "display/graphics.h"

#include "review.h"
#include "gamedata.h"
#include "Buzz_inc.h"
#include "game_main.h"
#include "place.h"
#include "port.h"
#include "sdlhelper.h"
#include "gr.h"
#include "gx.h"
#include "pace.h"

void DrawReview(char plr);
void PresPict(char poff);
void DrawRevText(char plr, int val);

struct mission_review_t {
    const char * Country;
    const char * Text;
} mission_review[] = {
    {
        .Country = "US",
        .Text = "THE PRESIDENT IS DEEPLY CONCERNED WITH\nRECENT SETBACKS AND IS MONITORING THE\nSITUATION.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT AWARDS YOU A CITATION FOR\nEXCELLENCE IN LEADERSHIP AND MANAGEMENT\nOF THE SPACE PROGRAM.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT PRAISES YOU HIGHLY FOR A\nCOMMANDING LEAD IN THE SPACE RACE.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT OFFERS HIGH PRAISE FOR YOUR\nSOUND JUDGEMENT AND ACCOMPLISHMENTS.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT IS PLEASED BY THE SOLID\nACCOMPLISHMENTS THAT HAVE GIVEN THE UNITED\nSTATES A COMMANDING LEAD IN THE EXPLORATION\nOF SPACE.",
    },
    {
        .Country = "US",
        .Text = "THE VICE PRESIDENT COMPLIMENTS THE OVERALL\nRESULTS THAT HAVE GIVEN THE UNITED STATES A\nSTRONG LEAD.",
    },
    {
        .Country = "US",
        .Text = "THE VICE PRESIDENT IS PLEASED THAT GOALS HAVE\nBEEN MET AND SCHEDULES ARE BEING MAINTAINED.",
    },
    {
        .Country = "US",
        .Text = "THE VICE PRESIDENT ACKNOWLEDGES THE MINIMAL\nRESULTS THUS FAR, AND URGES GREATER ACHIEVEMENTS\nTO TAKE THE LEAD.",
    },
    {
        .Country = "US",
        .Text = "THE VICE PRESIDENT REQUESTS THAT CLEAR GOALS\nBE ESTABLISHED AND MET.     ",
    },
    {
        .Country = "US",
        .Text = "THE VICE PRESIDENT WANTS RESULTS AND STATES\nTHAT PRIORITIES HAD BETTER BE ESTABLISHED.",
    },
    {
        .Country = "US",
        .Text = "THE VICE PRESIDENT STRONGLY URGES STRICTER\nMEASURES AND WILL CLOSELY MONITOR THE SITUATION.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT QUESTIONS SOME GUIDELINES, AND\nSTRONGLY URGES A CHANGEOVER IN PRIORITIES.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT IS NOT PLEASED WITH FAILURES, AND\nWARNS THAT CHANGES MUST BE MADE SOON.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT IS CONCERNED WITH THE FAILURE TO\nMEET GOALS AND IS GOING TO EVALUATE YOUR STRATEGY.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT QUESTIONS SOME OF YOUR DECISIONS\nAND WONDERS IF THE UNITED STATES CAN REGAIN\nTHE LEAD.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT IS UPSET WITH GROSS ERRORS IN\nJUDGEMENT AND WARNS THAT RESULTS HAD BETTER\nCOME QUICKLY.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT IS VERY DISAPPOINTED WITH YOUR\nLACK OF PROGRESS IN ALL AREAS OF THE SPACE\nPROGRAM. YOU'RE FIRED.",
    },
    {
        .Country = "US",
        .Text = "THE PRESIDENT IS VERY DISAPPOINTED WITH YOUR\nDISREGARD FOR SAFETY AND WILL TENDER YOUR\nRESIGNATION. YOU'RE FIRED.",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL IS VERY IRRITATED BY THESE\nSETBACKS AND IS GOING TO CLOSELY WATCH YOUR\nPROGRESS.",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL AWARDS YOU THE CITIZEN'S\nMEDAL FIRST CLASS OF THE SUPREME SOVIET FOR HEROIC\nBRAVERY AND LEADERSHIP IN THE DOMINATION OF SPACE.",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL AWARDS YOU A SEASIDE DACHA\nFOR YOUR SUPERB LEADERSHIP.",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL SPEAKS HIGHLY OF YOU AND\nTHE GLORIOUS ACCOMPLISHMENTS OF THE SUPERIOR\nSOVIET SPACE PROGRAM AT THE GENERAL ASSEMBLY.",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL IS PLEASED THAT THE SOVIET\nUNION HAS A COMMANDING LEAD IN THE CONQUEST OF\nSPACE.",
    },
    {
        .Country = "SOV",
        .Text = "THE POLITBURO IS PLEASED THAT THE SOVIET UNION\nHAS A STRONG LEAD IN SPACE EXPLORATION.",
    },
    {
        .Country = "SOV",
        .Text = "THE POLITBURO IS SATISFIED THAT GOALS HAVE BEEN\nMET AND SCHEDULES ARE BEING MAINTAINED.",
    },
    {
        .Country = "SOV",
        .Text = "THE POLITBURO WOULD LIKE TO SEE GREATER RESULTS\nIN ORDER TO HAVE A COMMANDING LEAD IN THE\nSPACE RACE.",
    },
    {
        .Country = "SOV",
        .Text = "THE POLITBURO HAS HIGH EXPECTATIONS AND REQUIRES\nTHAT THEY BE ACHIEVED.",
    },
    {
        .Country = "SOV",
        .Text = "THE POLITBURO IS A LITTLE IMPATIENT AND EXPECTS\nGREATER ACHIEVEMENTS AND GLORY IN THE CONQUEST\nOF SPACE.",
    },
    {
        .Country = "SOV",
        .Text = "THE POLITBURO IS RESTLESS AND DEMANDS GREAT\nACHIEVEMENTS IN THE CONQUEST OF SPACE.",
    },
    {
        .Country = "SOV",
        .Text = "THE POLITBURO DEMANDS THAT STRICTER MEASURES BE\nTAKEN. THEY ARE CLOSELY MONITORING YOUR\nPERFORMANCE.",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL QUESTIONS SOME OF YOUR\nGUIDELINES AND DEMANDS RESULTS, QUICKLY.",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL IS GROWING IMPATIENT WITH\nYOUR MANAGEMENT OF THE SPACE PROGRAM.",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL HAS ORDERED THE KGB TO\nINVESTIGATE YOUR BACKGROUND. HE IS VERY TIRED\nWITH THE LACK OF PROGRESS IN THE SPACE PROGRAM.  ",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL IS VERY ANGRY WITH FAILURES\nOF THE SPACE PROGRAM. HE QUESTIONS YOUR LOYALTY.",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL IS DISGUSTED WITH YOUR\nDISHONESTY AND INCOMPETENCE. YOU'VE LOST ALL YOUR\nTITLES AND POSSESSIONS. AFTER YOUR ARREST BY THE\nKGB, YOU'RE SENT TO SIBERIA FOR 'RE-EDUCATION'.",
    },
    {
        .Country = "SOV",
        .Text = "THE SECRETARY GENERAL IS DISGUSTED WITH YOUR\nDISHONESTY AND INCOMPETENCE. YOU'VE LOST ALL YOUR\nTITLES AND POSSESSIONS. AFTER YOUR ARREST BY THE\nKGB, YOU'RE SENT TO SIBERIA FOR 'RE-EDUCATION'.",
    },
};


void DrawReview(char plr)
{
    int clr, i, cte, P_value;
    char Fired_Flag = 0, Reset_Flag = 0;

    if (Data->P[plr].PresRev[0] != 0x7F) {
        FadeOut(2, display::graphics.palette(), 10, 0, 0);
    }

    PortPal(plr);
    gxClearDisplay(0, 0);

    if (Data->P[plr].PresRev[0] == 0x7F) {
        Fired_Flag = 1;
        Data->P[plr].PresRev[0] = 16;
    } else if (Data->P[plr].PresRev[0] >= 16) {
        Reset_Flag = 1;
        Data->P[plr].PresRev[0] = 15;
    }

    ShBox(0, 0, 319, 22);
    ShBox(0, 24, 319, 199);
    FlagSm(plr, 4, 4);
    RectFill(5, 28, 314, 195, 0);
    RectFill(5, 122, 314, 195, 0);
    ShBox(6, 123, 313, 194);
    RectFill(7, 124, 312, 193, 9);
    InBox(11, 128, 307, 189);
    RectFill(12, 129, 306, 188, 7);
    ShBox(6, 29, 177, 121);
    ShBox(179, 29, 313, 121);
    InBox(182, 32, 309, 117);
    InBox(3, 3, 30, 19);
    IOBox(243, 3, 316, 19);

    if (plr == 0) {
        DispBig(40, 5, "PRESIDENTIAL REVIEW", 0, -1);
    } else {
        DispBig(40, 5, "POLITBURO REVIEW", 0, -1);
    }

	display::graphics.setForegroundColor(1);
    PrintAt(257, 13, "CONTINUE");
	display::graphics.setForegroundColor(1);
    PrintAt(59, 36, "JOB PERFORMANCE");
	display::graphics.setForegroundColor(6);
    PrintAt(8, 46, "GOOD");
	display::graphics.setForegroundColor(1);
    PrintAt(8, 77, "FAIR");
	display::graphics.setForegroundColor(9);
    PrintAt(8, 109, "POOR");
	display::graphics.setForegroundColor(1);
    DispNum(154, 117, Data->Year - 1);
    DispNum(126, 117, Data->Year - 2);
    DispNum(97, 117, Data->Year - 3);
    DispNum(70, 117, Data->Year - 4);
    DispNum(42, 117, Data->Year - 5);
    RectFill(32, 39, 172, 111, 0);
    GradRect(33, 39, 171, 74, 0);
    GradRect(33, 75, 171, 110, 0);
	display::graphics.setForegroundColor(3);
    pline(60, 40, 60, 110);
    pline(88, 40, 88, 110);
    pline(116, 40, 116, 110);
    pline(144, 40, 144, 110);
    pline(33, 48, 171, 48);
    pline(33, 57, 171, 57);
    pline(33, 66, 171, 66);
    pline(33, 75, 171, 75);
    pline(33, 84, 171, 84);
    pline(33, 93, 171, 93);
    pline(33, 102, 171, 102);
    InBox(32, 39, 172, 111);

    for (i = 0; i < 5; i++) if (Data->P[plr].PresRev[i] > 16) {
            Data->P[plr].PresRev[i] = 16;
        }

    for (i = 0; i < 5; i++) {
        cte = 0;

        if (Data->P[plr].PresRev[i] < 8) {
            if (Data->P[plr].PresRev[i] == 7) {
                cte = 73;
            } else {
                cte = 40 + Data->P[plr].PresRev[i] * 5;
            }
        } else if (Data->P[plr].PresRev[i] > 8) {
            if (Data->P[plr].PresRev[i] == 9) {
                cte = 77;
            } else {
                cte = 80 + (Data->P[plr].PresRev[i] - 10) * 5;
            }
        };

        if (Data->P[plr].PresRev[i] == 8) {
            cte = 73;
        }

        RectFill(166 - i * 28, 75, 151 - i * 28, cte, 5 + ((Data->P[plr].PresRev[i] <= 8) ? 0 : 3));
		display::graphics.setForegroundColor(6 + ((Data->P[plr].PresRev[i] <= 8) ? 0 : 3));
        pline(167 - i * 28, 75, 167 - i * 28, cte);
    }

    if (Fired_Flag == 1) {
        clr = 0;

        for (i = 0; i < Data->P[plr].AstroCount; i++)
            if (Data->P[plr].Pool[i].Status == AST_ST_DEAD) {
                clr++;
            }

        Data->P[plr].PresRev[0] = (clr >= 2) ? 17 : 16;
    }

    DrawRevText(plr, Data->P[plr].PresRev[0]);

    if (Data->P[plr].PresRev[0] == 17) {
        Data->P[plr].PresRev[0] = 16;
    }

    P_value = 0;

    // 0 pres. 1 v.p.
    if (plr == 0) {
        if (Data->P[plr].PresRev[0] <= 4 || Data->P[plr].PresRev[0] >= 11) {
            P_value = 0;
        } else {
            P_value = 1;
        }
    };

    if (plr == 1) {
        if (Data->P[plr].PresRev[0] <= 4 || Data->P[plr].PresRev[0] >= 12) {
            P_value = 0;
        } else {
            P_value = 1;
        }
    }

    if (plr == 0) {
        if (Data->Year <= 60) {
            if (P_value == 0) {
                PresPict(0);
            } else {
                PresPict(1);
            }
        } else if (Data->Year >= 61 && Data->Year <= 63) {
            if (P_value == 0) {
                PresPict(2);
            } else {
                PresPict(3);
            }
        } else if (Data->Year >= 64 && Data->Year <= 68) {
            if (P_value == 0) {
                PresPict(4);
            } else {
                PresPict(5);
            }
        } else if (Data->Year >= 69 && Data->Year <= 73) {
            if (P_value == 0) {
                PresPict(6);
            } else {
                PresPict(7);
            }
        } else if (Data->Year >= 74 && Data->Year <= 76) {
            if (P_value == 0) {
                PresPict(8);
            } else {
                PresPict(9);
            }
        } else if (Data->Year >= 77) {
            if (P_value == 0) {
                PresPict(10);
            } else {
                PresPict(11);
            }
        }
    }

    if (plr == 1) {
        if (Data->Year < 61) {
            if (P_value == 0) {
                PresPict(14);
            } else {
                PresPict(15);
            }
        } else if (Data->Year <= 64) {
            if (P_value == 0) {
                PresPict(12);
            } else {
                PresPict(13);
            }
        } else if (Data->Year >= 65) {
            if (P_value == 0) {
                PresPict(16);
            } else {
                PresPict(17);
            }
        }
    }

    if (Reset_Flag == 1) {
        Data->P[plr].PresRev[0] = 16;
    }

    FadeIn(2, display::graphics.palette(), 10, 0, 0);

    return;
}


void Review(char plr)
{
    DrawReview(plr);
    music_start((plr == 0) ? M_PRES : M_RD);
    WaitForMouseUp();

    while (1) {
        key = 0;
        GetMouse();

        if (mousebuttons > 0 || key > 0) { /* Game Play */
            if ((x >= 245 && y >= 5 && x <= 314 && y <= 17) || key == K_ENTER) {
                InBox(245, 5, 314, 17);
                WaitForMouseUp();
                music_stop();
                return;  /* Done */
            }
        }
    }
}

// Mission Review

void MisRev(char plr, int pres)
{
    if (!AI[plr]) {
        music_start((pres > 0) ? M_SUCCESS : M_UNSUCC);
    }

    FadeOut(2, display::graphics.palette(), 10, 0, 0);
    gxClearDisplay(0, 0);
    ShBox(0, 0, 319, 22);
    InBox(3, 3, 30, 19);
    IOBox(243, 3, 316, 19);
    DispBig(40, 5, "MISSION REVIEW", 0, -1);
	display::graphics.setForegroundColor(1);
    PrintAt(258, 13, "CONTINUE");
    FlagSm(plr, 4, 4);

    key = 0;
    Draw_Mis_Stats(plr, Data->P[plr].PastMis - 1, 0, 1);
    key = 0;
    gxClearDisplay(0, 0);
    return;
}


void PresPict(char poff)
{
    GXHEADER local;
    SimpleHdr table;
    FILE *in;
    in = sOpen("PRESR.BUT", "rb", 0);
    fseek(in, poff * sizeof_SimpleHdr, SEEK_SET);
    fread_SimpleHdr(&table, 1, in);
    fseek(in, table.offset, SEEK_SET);
    fread(&display::graphics.palette()[96], 672, 1, in);
    fread(buffer, table.size, 1, in);
    fclose(in);
    GV(&local, 126, 84);
    RLED_img(buffer, local.vptr, table.size, local.w, local.h);

    gxPutImage(&local, gxSET, 183, 33, 0);

    DV(&local);
    return;
}

void CalcPresRev(void)
{
    int16_t *ip;
    int val, max, min, i, j;
    char plr;

    if (Data->Year == 57 && Data->Season == 0) {
        return;
    }

    // Move PresRev down One
    for (j = 0; j < NUM_PLAYERS; j++)
        for (i = 4; i > 0; i--) {
            Data->P[j].PresRev[i] = Data->P[j].PresRev[i - 1];
        }

    Data->P[0].Prestige = Data->P[1].Prestige = 0; // Clear Prest when finished

    for (plr = 0; plr < NUM_PLAYERS; plr++) {
        ip = &Data->P[plr].PresRev[0];

        max = maxx(Data->P[plr].tempPrestige[0], Data->P[plr].tempPrestige[1]);
        min = minn(Data->P[plr].tempPrestige[0], Data->P[plr].tempPrestige[1]);

        val = ((max >= 0 && min >= 0) || (max <= 0 && min <= 0)) ? max + min : max / 2 + min;

        *ip = (val < 0 && (*ip < 4)) ? *ip + 1 : ((val > 1 && val <= 10) ? *ip - 1
                : ((val >= 11 && val <= 20) ? ((*ip < 4) ? *ip - 1 : *ip - 2)
                       : ((val >= 21) ? ((*ip < 4) ? *ip - 1 : *ip - 3)
                          : ((val >= -9 && val <= 0) ? *ip + 1 : ((val <= -10) ?
                                  ((plr == 0) ? *ip + Data->Def.Lev1 + 1 : *ip + Data->Def.Lev2 + 1) : *ip)))));

        *ip = (*ip > 16) ? 16 : ((*ip < 1) ? 1 : *ip);

        Data->P[plr].tempPrestige[0] = 0;
        Data->P[plr].tempPrestige[1] = 0;
        Data->P[plr].PresRev[0] += (Data->P[plr].PresRev[0] > Data->P[abs(plr - 1)].PresRev[0]) ? 1 : 0;
    }

}

void DrawRevText(char plr, int val)
{
    
    // Read Mission Structure
    const char * review_text = mission_review[18 * plr + val].Text;

	display::graphics.setForegroundColor(1);

    grMoveTo(20, 140);

    int line = 0;
    for (int i = 0; review_text[i]; i++) {
        if (review_text[i] == '\n') {
            line++;
            grMoveTo(20, 140 + 12 * line);
        } else {
            DispChr(review_text[i]);
        }
    }
}


/* EOF */

