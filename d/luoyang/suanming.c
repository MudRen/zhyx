inherit ROOM;

void create()
{
	set("short", "é����");
	set("long", @LONG
����һ������бб��é���ݣ�ǽͷ����ɫ�ܹ֣�һ��Ѫɫ�����İ���
ɫ��������ǹ���ɭɭ�������޴���һյ�͵ƺ�����������̫������ͼΪ
�׵���������׭����š����ࡹ���֣�Ҳ�������޹�ĺ�ɫ��
LONG);
	set("no_clean_up", 0);
    set("no_sleep_room",1);
	set("exits", ([
  		"south" : __DIR__"hutong3",
	]));

              set("objects",([ 
                          "/adm/npc/qingyangzi":1,
              ])); 

	setup();
        //replace_program(ROOM);
}