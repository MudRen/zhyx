//Room: majiu1.c ���
//Date: Oct. 2 1997 by That

#include <room.h>

inherit ROOM;

void create()
{
      set("short","���");
      set("long",@LONG
���ǿ͵�����ǣ����깩Ӧ���ʲ��ϡ�������紾�ӣ�����ǻ��
��ǣ����Ǻ����տ���������ι�����㣬��ϴˢ�ø�Ǭ������һֱ�ź�
������·��
    ����жѷ������Ѳ��ϣ�������һ����ۡ�
LONG);
      set("outdoors", "yangzhou");
      set("no_fight", "1");
      set("no_beg", "1");
      set("no_clean_up", 0);
      set("objects", ([
              "/clone/horse/zaohongma": 3,
              "/clone/horse/huangbiaoma": 3,
              "/clone/horse/ziliuma": 3,
      ]));
      set("exits",([ /* sizeof() == 1 */
          "west"      : __DIR__"market",
      ]));
      setup();
}
