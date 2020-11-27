// Room: /d/huashan/sgyhole.c

inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
����һ���������۵�ɽ�������������ʯ����ȴ��������
�����������Ѿ�ʧ���ľ�����С�������ʯ��(wall)�Ϻܶ�С
�ˣ�ȫ�����������ƣ������������֮������ʮ�����
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "south"   : __DIR__"sgyhole4",

        ]));
        set("item_desc", ([ 
            "wall" : @TEXT

       o    | o      o    \ o      o      o     <o     <o>
    --^|\    ^|^  --v|^    v|v    |/v   \|X|    \|      |
       /\     >\    /<      >\    /<      >\    /<      >\

       o>     o      o      o      o      o      o      o
       \ __   x     </     <|>    </>    <\>    <)>     |\__
      /<      >\    /<      >\    /<      >\     >>     L
TEXT
        ]));

        setup();
}
void init()
{
        add_action("do_mianbi", "mianbi");
}

int do_mianbi()
{
        object ob;
        int c_skill;

        ob = this_player();

        c_skill = (int)ob->query_skill("wuyue-shenjian", 1);

		if (ob->query("family/family_name") != "��ɽ��"
		&& ob->query("family/family_name") != "��ɽ��"
		&& ob->query("family/family_name") != "��ɽ��")
		{
			write("����������������������������о������ʽ��\n", ob);
                return 1; 
		}

		if (!ob->query("can_perform/huashan-jian/xian"))
		{
			write("��û�����򵽻�ɽ�����ľ��У������������ɽ���û�а취���������񽣡�\n", ob);
            return 1; 
		}			   

		if (!ob->query("can_perform/wushen-jian/shen"))
		{
			write("��û�����򵽺�ɽ���񽣵ľ��У�����Ԫ�ƣ�û�а취���������񽣡�\n", ob);
            return 1; 
		}			   

		if (!ob->query("can_perform/poyang-jian/long"))
		{
			write("��û��������ɽ������⽣�ľ��У�����������û�а취���������񽣡�\n", ob);
            return 1; 
		}  
		

		if (ob->query_skill("martial-cognize", 1) < 300)
		{
			write("����������񽣼�����£������Լ�����ѧ����������⡣\n", ob);
            return 1; 
		}               

        if ((int)ob->query("max_neili") < 5000)
		{
			write("���������Ϊ������û�а취�������񽣡�\n", ob);
            return 1; 
		}               

        if ((int)ob->query_skill("sword", 1) < 300)
		{
			write("��Ļ�������̫�û�а취�������񽣡�\n", ob);
            return 1; 
		}  

        if (! ob->can_improve_skill("wuyue-shenjian"))
        {
                write("���ʵս���鲻�㣬�޷�����ʯ�����ݡ�\n");
                return 1; 
        }

        if (ob->query("jing") < 50)
        {
                write("�㾫�����ܼ��У������޷�����ʯ�����ݡ�\n");
                return 1; 
        }

        if (c_skill > 300)
        {
                write("�����ʯ������̫��ǳ�ˡ�\n");
                return 1;
        }

        if (ob->is_busy()) 
              { 
                     write("��Ŀǰ��æ�أ������޷�����ʯ�����ݡ�\n"); 
                      return 1;  
              } 

        message_vision("$N�����ʯ��������˼�����ã��ԡ������񽣡�"
                        "��������\n", ob);
        ob->improve_skill("wuyue-shenjian", ob->query("int"));
        ob->receive_damage("jing", 45);
        ob->start_busy(random(2));
        return 1;
}
