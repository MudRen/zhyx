// �ָ�һ�����ܡ�һ��Ǳ�ܼ��ٷ�֮���������ҩ������ʦ���գ���name�����м�¼

#include <ansi.h>
inherit ITEM;
int do_eat(string);
int do_name(string);
void setup()
{}

void init()
{
    add_action("do_eat", "eat");
    add_action("do_name","name");
}

void create()
{
    set_name(HIB"�£գ������ֲ���"NOR, ({"mibu dan", "dan"}));
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("unit", "��");
        set("long", "����һ���ǳ������ҩ�裬��˵һ�Ծ�������Ҳ������ĳЩ��Ч��\n");
    }
    setup();
}

int do_eat(string arg)
{
    int i,level,exp,pot;
    object me;
    mapping skill_status;
    string *sname;
    me = this_player();
    skill_status = me->query_skills();
    
    if (!id(arg))
        return notify_fail("��Ҫ��ʲô��\n");
    if( !living(me) )
    return notify_fail("ʲô��\n");
    if(!query("me_id")||query("me_id")!=me->query("id"))
        return notify_fail("��������һ�Ծ�����һ��ҧ��ȥ������ѽ�����̵øϽ��³�������������һȦ�ݣ�\n");
    sname = keys(skill_status);
    for(i = 0; i < sizeof(skill_status); i++)
    {
        level = skill_status[sname[i]] + 1;
        me->set_skill(sname[i], level);
    }
    exp  = me->query("combat_exp");
    me->set("combat_exp", exp*100/95);
    pot = (me->query("potential")-me->query("learned_points"));
    me->add("potential",pot);
    me->add("max_neili",20);
    write_file("/log/clone/1794_eat",sprintf("(%s)%s(%s)����һ�Ծ�����һ��\n", ctime(time()),me->name(),me->query("id")));
    write("��ʧȥ�ļ��ܡ�Ǳ�ܺ;��鱻�����ָ������ˡ�\n");
    destruct(this_object());
    return 1;
}

int do_name(string arg)
{
    object me;
    me = this_player();
    if( !wizardp(me)) return 0;
    if(!arg) return notify_fail("name id!\n");
    set("me_id",arg);
    write("����һ�Ծ���������Ϊ"+arg+"ר�õģ������޷��ԣ�\n");
    return 1;
}

