
inherit ROOM;

void create()
{ 
        set("short", "�޼�����ǰ");
        set("long",@LONG
�������޼��ﱱ���ֲ��Ĵ���ǰ�棬�޼�����������ֻ�Ƿ�
����������ڣ���ʹ��ˣ���������Ҳ��ķ����Ȼ������һ�ۿ�
��ȥ���;������Ʋ�����
LONG );
        set("outdoors", "beijing");
        set("exits", ([
                "west" :  __DIR__"yongdingdao",
                "east" : __DIR__"wjb_bjwdt",
        ])); 
        set("objects", ([   
             __DIR__"npc/wjb-guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "east") 
        {
           if (! me->query_temp("good_wjb2") && me->query("bang_good/name") != "�޼���")
               return notify_fail("����һ����ס�㣬�����ȵ������޼������������˵���������\n"); 
           else
           {
              me->delete_temp("good_wjb2");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

