
inherit ROOM;

void create()
{ 
        set("short", "�޼�����ǰ");
        set("long",@LONG
�������޼��������ܲ��Ĵ���ǰ�棬�޼�����������ֻ�Ƿ�
����������ڣ���ʹ��ˣ���������Ҳ��ķ����Ȼ������һ�ۿ�
��ȥ���;������Ʋ�����
LONG );
        set("outdoors", "xiangyang");
        set("exits", ([
                "west" :  __DIR__"xiaorong1",
                "north" : __DIR__"wjb_dating",
        ])); 
        set("objects", ([   
             __DIR__"npc/wjb-guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
        {
           if (! me->query_temp("good_wjb") && me->query("bang_good/name") != "�޼���")
               return notify_fail("����һ����ס�㣬�����ȵ������޼������������˵���������\n"); 
           else
           {
              me->delete_temp("good_wjb");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

