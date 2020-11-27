// �Ϲ�ʮ������֮ ��ԯ��
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

#include <weapon.h>
inherit SWORD;

int is_magic_item() { return 1; }

mapping skills = ([
        "egui-dao"     :   "�����",
        "xiuluo-dao"   :   "���޵�",
        "renjian-dao"  :   "�˼��",
        "chusheng-dao" :   "������",
        "tianji-dao"   :   "�켫��",
        "diyu-dao"     :   "������",
        "lun"          :   "�桤�����ֻ�",
]);

void create()
{
        set_name(HIY "��ԯ��" NOR, ({ "xuanyuan jian", "xuanyuan", "jian" }) );
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIY "�����Ϲ�����֮�ף�ӵ�����������������˵"
                                "ӵ�д˽��߿ɳ۳��ˡ�ħ�������磬�Ʋ��ɵ���\n"
                                "��������˸�����ֵ����֣����Ƿ�̾��ġ�\n"
                                "ת����ɴӴ˽�������(lingwu)��ת����ѧ�������ֻؽ���\n"
                                "lingwu ?���ɲ鿴���������ʽ��\n" NOR);
                set("material", "gold");
                set("wield_msg", HIY "$N" HIY "һ���������������������£�ӵ��һ��������\n"
                                 "�����񽣣�ɲ�Ǽ�˽�����һ�����ǻ���������$N" HIY "���С�\n" NOR);                               
                set("unwield_msg", HIY "$N" HIY "����һת����ԯ���ѹ��ʡ�\n" NOR);
                set("stable", 100);

        }
        init_sword(500);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;
        
        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(20 + random(20));
                return HIY "$N" HIY "���������е���ԯ��������ʹ����ж�����ֱ�Ƶ�"
                           "$n" HIY "�������ˡ�\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIR "$N" HIR "��ת������ԯ������Ȼ�䣬������⻮��$n" HIY "��$n" HIY
                           "������䣬ȴ���н���\n" NOR;

        }
        return damage_bonus;
}

void init()
{
        add_action("do_lingwu", "lingwu");       
}

int do_lingwu(string arg)
{
        object me;
        int i;
        string *str;        
               
        me = this_player();

        if(! objectp(present("xuanyuan jian", me)))return 0;
 
        // ת�����������
        if (! me->query("scborn/ok"))return 0;
                
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");

        if (! arg)return notify_fail("��Ҫ����ʲô��\n");
        
        str = keys(skills);
        if (arg == "?")
        {
        	write(HIC "��ԯ���м��������¾�ѧ��\n" NOR);
        	for (i = 0; i < sizeof(str); i ++)
        	        write(sprintf(HIC "%-20s %s\n", 
        	              str[i], skills[str[i]]));
        	              
        	return 1;
        	      
        }
        if (member_array(arg, str) == -1)       
                    return notify_fail("��Ҫ����ʲô(lingwu ?)��\n");

        if (me->query_skill("buddhism", 1) < 200)
                    return notify_fail("�㷭����ȥ���о������澭�ģ�ȴʼ�տ������ס�\n");
                                                        
        if (me->query_skill("literate", 1) < 200)
                    return notify_fail("�����д�ֵȼ��������ܶ���˼���޷���⡣\n");

        if (me->query_skill("sword", 1) < 300)
                    return notify_fail("�������������㣬�޷������ʲô��\n");                    

        if (me->query_skill("force", 1) < 300)
                    return notify_fail("������ڹ���Ϊ���㣬�޷������ʲô��\n");
                    
        if (me->query_skill("dodge", 1) < 300)
                    return notify_fail("������Ṧ��Ϊ���㣬�޷������ʲô��\n");                    

        if (arg == "lun" && me->query_skill("liudao-jian", 1) < 450)
                    return notify_fail("�������ֻؽ����ȼ�������\n");
                    
        else if (arg == "lun" && me->query_skill("force", 1) < 680)
                    return notify_fail("���ڹ���Ϊ���㡣\n");

        else if (arg == "lun" && me->query("max_neili") < 20000)
                    return notify_fail("��������Ϊ���㡣\n");        

        else
        {
        	if (me->query_skill(arg, 1))
        	       return notify_fail("�㲻�Ѿ�������������\n");

                message_vision(HIM "$N" HIM "�۾�����ز�������ԯ���еİ��ء�����\n" NOR, me);
                
        	switch(arg)
        	{
        		case "lun":
        		    write(HIG "��������˾��С��桤�����ֻؽ�����\n" NOR);
        		    me->set("can_perform/liudao-jian/lun", 1);
        		    destruct(this_object());
        		    return 1;
        		
        	        default :        	            
        	            write(HIC "������� " + skills[arg] + " ��\n" NOR);
        	            me->set_skill(arg, 1); // �����һ��
        	            destruct(this_object());
        	            return 1;
        	}
        }

        return 1;
}
