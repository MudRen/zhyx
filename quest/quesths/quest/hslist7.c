#include <ansi.h>

mapping *quest = ({
	([
		"id" :    "yue er",
                "name" :  "�¶�",
                "bonus":  75,
                "type":   "ɱ",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "����",
                "bonus":  50,
                "type":   "Ѱ",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "����",
                "bonus":  60,
                "type":   "��",
                "object": "/d/city/obj/cloth.c",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "����",
                "bonus":  60,
                "type":   "��",
                "object": "/d/city/obj/cloth.c",
        ]),
});

mapping query_quest()
{
        return quest[random(sizeof(quest))];
}
