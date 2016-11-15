//#include "Ammo.h"
//
//Ammo::Ammo(std::string n, b2Body* ammo_body, float velo, int dmg, int pen, float x, float y) :Object()
//{
//	this->ammo_body = ammo_body;
//	texture_name = n +".png";
//	set_texture(texture_name);
//	object_texture.setSmooth(true);
//
//	velocity = velo;
//	damage = dmg;
//	penetration = pen;
//	timer = 60 * 2;
//	is_hit = false;
//}
//
//Ammo::Ammo() :Object()
//{
//	texture_name = "ammo.png";
//	set_texture(texture_name);
//	object_texture.setSmooth(true);
//
//	velocity = 2.0;
//	damage = 15;
//	penetration = 35;
//}
//
//void Ammo::on_update(sf::RenderWindow* win)
//{
//	timer--;
//	x = get_position().x*30.0f;
//	y = get_position().y*30.0f;
//	sprite_name.setRotation(ammo_body->GetAngle()*180.0f/b2_pi);
//	sprite_name.setPosition(x, y);
//}
//
//int Ammo::get_damage()
//{
//	return damage;
//}
//
//int Ammo::get_penetration()
//{
//	return penetration;
//}
//
//void Ammo::set_position(float x, float y)
//{
//	this->x = x;
//	this->y = y;
//}
//
//void Ammo::on_draw(sf::RenderWindow* win)
//{
//	if (is_hit)
//		sprite_name.setColor(sf::Color(0, 0, 0));
//	else
//		sprite_name.setColor(sf::Color(255,255,255));
//	win->draw(sprite_name);
//}
//
//float Ammo::get_velocity()
//{
//	return velocity;
//}
//
//Ammo::~Ammo()
//{
//
//}
//
//void Ammo::set_velocity(float x, float y)
//{
//	ammo_body->SetLinearVelocity(b2Vec2(x, y));
//}
//
//void Ammo::start_contact()
//{
//	is_hit = true;
//}
//
//void Ammo::end_contact()
//{
//	is_hit = false;
//}
//void Ammo::set_coord(float _x, float _y)
//{
//	x = _x;
//	y = _y;
//}
//
//b2Vec2 Ammo::get_position()
//{
//	return ammo_body->GetPosition();
//}
//b2Body* Ammo::get_ammo_body()
//{
//	return ammo_body;
//}
//
//void Ammo::set_rotation(float rot)
//{
//	ammo_body->SetTransform(b2Vec2(get_position().x, get_position().y), rot);
//}
//
//int Ammo::get_timer()
//{
//	return timer;
//}