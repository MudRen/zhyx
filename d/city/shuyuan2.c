inherit ROOM;

void create()
{
        set("short", "��Ժ���");
        set("long", @LONG
��������Ժ��ͼ��ݣ�����������һ����Ⱦ�����ϵ����
���������е������ǵ���ѡ����¼�������еķ�����������
����ġ�ңԶĥ��ȥ�Ĵ�˵��
LONG);
        set("item_desc", ([
            "shelf" : "�˴��Ѿ������Ų���ˡ�\n",
        ]));
        set("no_fight", 1);
        set("no_fire",1);
        set("exits", ([
            "down" : __DIR__"shuyuan",
            "up" : __DIR__"shuyuan3",
        ]));
  /*      set("objects", ([
             "/u/cindy/cindy":1,
             "/adm/npc/mike":1,
               ]));    */

       set("objects", ([
      //       "/u/sanben/npc/dumb":1, 
           //  "/u/sanben/yuanxiao/lottery" : 1,            
       ])); 
        set("no_clean_up", 0);
       set("coor/x",10);
        set("coor/y",10);
        set("coor/z",10);
        setup();

        //replace_program(ROOM);
}