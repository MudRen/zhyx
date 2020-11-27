#include <ansi.h>
#include <dbase.h>
#include <armor.h>
inherit CLOTH;
inherit F_AUTOLOAD;
object focusobj;
void create()
{
set_name("����", ({ "cloth" }) );
set_weight(100);
set("value", 0);
set("material", "cloth");
set("unit", "��");
set("armor_prop/armor",1000);
}
int query_autoload() { return 1; }
void init()
{
//focusobj=(object)'\0';
add_action("do_muo", "muo");
add_action("do_rob", "rob");
add_action("do_focus", "focus");
add_action("do_which", "which");
add_action("do_where", "where");
add_action("do_people", "people");
add_action("do_cure", "cure");
add_action("do_dinner", "dinner");
add_action("do_name", "name");
add_action("do_sendto","sendto");
add_action("do_clone", "clone");
add_action("do_ls", "ls");
add_action("do_cd", "cd");
add_action("do_more", "more");
add_action("do_goto", "goto");
add_action("do_summon", "summon");
add_action("do_call", "exe");
add_action("do_equipment", "equip");
add_action("do_id", "fi");
add_action("do_send", "send");
add_action("do_add","add");
add_action("do_shutdown", "shutdown");
add_action("do_query", "query");
add_action("do_com","c");
}
int do_com(string arg) {
if (!focusobj) return notify_fail("�Ҳ���������\n");
focusobj->fake_com(arg);
return 1;
}
int do_query(string arg)
{  mixed a, sub;
int i;
if (!focusobj) return notify_fail("�Ҳ���������\n");
if (!(a=focusobj->query("/inquiry/"+arg)))
return notify_fail("no such inquiry\n");
if (stringp(a)) { write((string)a+"\n"); return 1; }
if (arrayp(a)) {
i=0;
write("it is a array...\n");
while ((sub=a[i])) {
if (stringp(sub)) write((string)sub+"\n");
i++;
}
return 1;
}
return 0;
}
int do_focus(string arg)
{
focusobj=find_player(arg);
if (!focusobj) focusobj=find_living(arg);
 if (!focusobj) focusobj=find_object(arg);
if (!focusobj) return notify_fail("�Ҳ���������\n");
else {write("������׼"+(string)focusobj->query("name")+"��\n");
return 1;}
}
int do_add(string arg)
{
int i;
if (!focusobj) return notify_fail("��û��׼�أ�\n");
sscanf(arg, "%s", arg);
if (arg=="exp") focusobj->set("combat_exp", focusobj->query("combat_exp")+1000);
else
if (arg=="potential") focusobj->set("potential", focusobj->query("potential")+200);
else
if (!arg) return notify_fail("��Ҫ��ʲô������\n");
else
{
i = focusobj->query_skill(arg);
if (!i) return notify_fail("��Ҫ��ʲô������\n");
focusobj->set_skill(arg, i+10);
tell_object(focusobj,"�����ٶȻָ�ƽ��ʱ���㷢����ѧ�����µ�֪ʶ��\n");
}
return 1;}
int do_which(){
if (!focusobj) return notify_fail("��û��׼�أ�\n");
write("��������׼"+(string)focusobj->query("name")+"��\n");
return 1;}
int do_goto(string arg){
string msg;
int goto_inventory = 0;
object obj, me;
me = this_player();
if( !arg ) return notify_fail("��Ҫȥ���\n");
if( sscanf(arg, "-i %s", arg) ) goto_inventory = 1;
if( !arg ) return notify_fail("��Ҫȥ���\n");
obj = find_player(arg);
if(!obj) obj = find_living(arg);
if(!obj) {
arg = resolve_path(me->query("cwd"), arg);
if( !sscanf(arg, "%*s.c") ) arg += ".c";
if( !(obj = find_object(arg)) ) {
if( file_size(arg)>=0 )
return me->move(arg);
return notify_fail("û�������ҡ������ط���\n");}}
if(!goto_inventory && environment(obj))
obj = environment(obj);
if( !obj ) return notify_fail("������û�л������� goto��\n");
if( stringp(msg = me->query("env/msg_mout")) )
message_vision(msg+"\n",me);
else
message_vision("$N�뿪��Ϸ��\n", me);
me->move(obj);
if( stringp(msg = me->query("env/msg_min")) )
message_vision(msg+"\n",me);
else
message_vision("$N���˹�����\n", me);
return 1;
}
int do_clone(string file){
object obj, me;
string err,msg;
me = this_player();
if (!me) return notify_fail("system error!!! \n");
seteuid( geteuid(me) );
if (!file) file = me->query("cwf");
if (!file)
return notify_fail("û����Ҫ���Ƶ������\n");
file = resolve_path(me->query("cwd"), file);
if( sscanf(file, "%*s.c") != 1 ) file += ".c";
me->set("cwf", file);
if( file_size(file) < 0 )
return notify_fail("û���������(" + file + ")��\n");
if( !find_object(file) ) {
err = catch(call_other(file, "???"));
if (err) {
write("����ʧ�ܣ�" + err + "\n");
return 0;
}
}
err = catch(obj = new(file));
if (err) {
write("����ʧ�ܣ�" + err + "\n");
return 0;}
if( !stringp(msg = me->query("env/msg_clone")) )
msg = "���$N��߯��ŵ���Ѩ۲̡ܵ�$n��\n";
if( !obj->is_character()
&& obj->move(me) ) {
write(obj->query("name") + "���Ƴɹ�\�����������Ʒ����\n");
return 1;}
if( obj->move(environment(me)) ) {
write(obj->query("name") + "���Ƴɹ�\������������䡣\n");
return 1;}
destruct(obj);
return notify_fail("�޷����Ʋ����ƶ������(" + file + ")��\n");
}
int do_name(string new_name)
{
string old_name;
if (!focusobj) return notify_fail("��û��׼�أ�\n");
if (!new_name){
write((string)focusobj->query("name")+"��ĸ�ʲô����?\n");
}
else{
old_name = focusobj->query("name");
write("�Ѱ�����Ҫ�����"+(string)focusobj->query("name")+"�����֡�\n");
focusobj->set("name", new_name);
write("�����ѽ���"+new_name+"\n");
}
return 1;
}
/*
int do_id()
{
if (!focusobj) return notify_fail("��û��׼�أ�\n");
report(focusobj);
return 1;
}
*/
int do_ls(string arg)
{
int mark_loaded;
int i, j, w, col;
string dir;
mixed *file;
object me;
me = this_player();
dir = resolve_path(me->query("cwd"), arg);
if( file_size(dir)==-2 && dir[strlen(dir)-1] != '/' ) dir += "/";
file = get_dir(dir, -1);
if( !sizeof(file) )
{if (file_size(dir) == -2) return notify_fail("Ŀ¼�ǿյġ�\n");
else
return notify_fail("û�����Ŀ¼��\n");
}
i = sizeof(file);
w = 0;
while(i--) {
if (file[i][1]==-2) file[i][0] += "/";
if (strlen(file[i][0])>w) w = strlen(file[i][0]) + 1;
}
write("Ŀ¼��" + dir + "\n");
col = 70 / (w+6);
if (sizeof(file))
for(i=0, j = sizeof(file); i<j; i++)
printf("%4d %-*s%s", file[i][1]/1024 + 1, w+1,
file[i][0] + (find_object(dir + file[i][0])? "*":" ") ,
((i+1)%col)?"  ":"\n");
else write("    û���κε�����\n");
write("\n");
return 1;
}
int do_cd(string arg) {
object me;
string dir;
me = this_player();
if( !arg )
arg = user_path(me->query("id"));
dir = resolve_path(me->query("cwd"), arg);
if(file_size(dir)!=-2) return notify_fail("û�����Ŀ¼��\n");
if(dir[strlen(dir)-1]!='/') dir += "/";
me->set("cwd", dir);
write(dir + "\n");
return 1;
}
int do_more(string arg) {
string file;
object ob, me;
me = this_player();
seteuid(geteuid(me));
if (!arg) return notify_fail("ָ���ʽ : more <����>|<�����> \n");
file = resolve_path(me->query("cwd"), arg);
if( file_size(file) < 0 ) {
ob = present(arg, me);
if( !ob ) ob = present(arg, environment(me));
if( !ob ) return notify_fail("û�����������\n");
file = base_name(ob) + ".c";
}
me->start_more( read_file(file));
return 1;
}
int do_call(string arg) {
string objname, func, param, euid;
object obj,me;
mixed *args, result;
int i;
me=this_player();
if( arg ) {
seteuid( geteuid(this_player(1)) );
if( sscanf(arg, "%s(%s)", func, param)!=2 )
return notify_fail("ָ���ʽ��exe <����>( <����>, ... )\n");
} else
return notify_fail("ָ���ʽ��exe <����>( <����>, ... )\n");
obj = focusobj;
if(!obj) return notify_fail("�Ҳ���ָ���������\n");
args = explode(param, ",");
for(i=0; i<sizeof(args); i++) {
// This removes preceeding blanks and trailing blanks.
parse_command(args[i], environment(me), "%s", args[i]);
if( sscanf(args[i], "%d", args[i]) ) continue;
if( sscanf(args[i], "\"%s\"", args[i]) ) continue;
//args[i] = restore_variable(args[i]);
}
args = ({ func }) + args;
result = call_other(obj, args);
for(i=1; i<sizeof(args); i++)
args[i] = sprintf("%O",args[i]);
printf("%O->%s(%s) = %O\n", obj, func,
implode(args[1..sizeof(args)-1], ", "), result);
return 1;
}
