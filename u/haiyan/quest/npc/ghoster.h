// ghoster.h
// Modified by haiyan

int accept_object(object who, object ob);  
int do_shou(string arg);
void wildghost(object me);
void course(object me, object weapon);

void init()
{
    object me; 
    ::init(); 
    me = this_player(); 
    if (me->query_temp("gui/shougui"))
    {
        if (query_temp("player") == me->query("id"))
        {
            tell_object(me, comeon);
            call_out("wildghost", 1, me);
            add_action("do_shou", "shoufu");
        }
    }
}

int do_shou(string arg)
{
    object weapon, me, ob; 
    me = this_player(); 

    if (me->is_busy())
       return notify_fail("����һ��������û����ɡ�\n");

    if (!present("fu zhi", me))
        return notify_fail("��û��ֽ�����չ����Ĺ�������ˣ�\n");

    if (!present("taomu jian", me))
        return notify_fail("��û����ľ���������չ����Ĺ�������ˣ�\n");

    weapon = me->query_temp("weapon");
    if (!objectp(weapon))
         return notify_fail("��û��װ����ľ������Ҳ�����㣡\n");

    if (weapon->name() == "��ľ��")
         return notify_fail("������ľ��ֻ���������棬��������\n");

    if (weapon->name() != HIM"��ľ��"NOR)
         return notify_fail("��û��װ����ľ������Ҳ�����㣡\n");

    if (!objectp(ob = me->query_temp("handing")) ||
         ob->name() != HIY"��ֽ"NOR)
         return notify_fail("������û���÷�ֽ���޷��ù������\n");

    me->start_busy(2);
    if (query("env/invisible"))
    {
        message_vision(HIY"$N������" + ob->name() + HIY"����һ�٣�ɲʱ����"
                       "ҫ�۵Ľ�⡣$N���һ������ħ���������������\n"NOR, me);
        if (random(3) < 1)
        {
            message_vision(HIR"$N��Ȼ����һ��$n��������צ��$N������\n"NOR, me, this_object());
            delete("env/invisible"); 
        }
    }
    else
    {
        message_vision(styb[random(sizeof(styb))], me, this_object());
        call_out("course", 1, me, weapon);
    }
    return 1;
}

void wildghost(object me)
{
    int damage;
    damage = query_temp("damage", 1);
    if (random(10)==0) command("grin " + me->query("id")); 
    if (present(this_object(), environment(me)))
    {
       if (random(10) < 5)
       {
           message_vision(stya[random(sizeof(stya))], me, this_object());
           me->receive_damage("qi", damage, this_object());
           me->receive_wound("qi", damage/3, this_object());
       }
       call_out("wildghost", 1, me);
    }
}

void course(object me, object weapon)
{
    int ap, dp, dam;
    object dan;
    ap = me->query_skill("taoism", 1);
    dp = query_skill("claw", 1);
    if (ap < 300)   dam = 160;
    if (ap < 200)   dam = 120;
    if (ap < 100)   dam = 80;
    if ( ap / 2 + random(ap) > dp )
    {
       message_vision(HIR "$NͻȻ����һ�������ĲҽУ�����ë���Ȼ��\n"NOR, this_object());
       if (random(10) < 3)
       {
          message_vision(HIY"\n" + weapon->name() +
                         HIY "ͻȻ���ֶ���������һ����⣬������$n���ʺ�\n\n"
                         HIR "ֻ��һ�������ļ�У�$n���ڵ���Ť���˼��£�"
                         HIR "����������һ̲��ˮ����ʧ�ˡ�\n\n", me, this_object());
          weapon->move(environment(this_object()));
          me->set_temp("gui/finish", 1);
          dam += random(80);
          me->set_temp("gui/base", dam);
          if (random(5) == 0)
          {
              message_vision(HIG "$NͻȻ����������һ�ŷ����̹�ĵ��裬С�ĵؼ���������\n"NOR, me);
              dan = new("/u/haiyan/quest/obj/rendan");
              dan->move(me);
          }
          destruct(this_object());
       }
    }
}

void check_time()
{
     if (time() - query_temp("born_time") > 1200) 
     {
         message_vision(HIB "һ�����紵���������ָֻ���ƽ����\n"NOR, this_object());
         destruct(this_object());
     }
}

int accept_fight(object ob)  
{ 
    return notify_fail("�㲻�ܸ���������\n");  
} 
int accept_hit(object ob)  
{ 
    tell_object(ob,"�㲻�ܸ�����ܡ�\n");
    return 0; 
} 
int accept_kill(object ob)  
{ 
    return notify_fail("�㲻�ܸ�����ܡ�\n");  
} 
int accept_touxi(object ob)  
{  
    tell_object(ob,"�㲻��͵Ϯ��ꡣ\n");
    return 1;  
}  
int accept_ansuan(object ob)  
{
    return notify_fail("�㲻�ܰ����ꡣ\n"); 
}

