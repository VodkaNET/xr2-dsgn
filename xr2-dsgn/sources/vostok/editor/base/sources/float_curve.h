////////////////////////////////////////////////////////////////////////////
//	Created		: 03.02.2011
//	Author		: Andrew Kolomiets
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef FLOAT_CURVE_H_INCLUDED
#define FLOAT_CURVE_H_INCLUDED

namespace vostok {
namespace editor_base {

	ref class float_curve_type_editor;
	ref class color_curve_type_editor;
	using namespace System;
	using namespace System::Drawing;
	using System::Collections::ObjectModel::ReadOnlyCollection;
	

public ref struct float_curve_pair: public System::IComparable
{
	float_curve_pair(float t, float v):time(t), value(v){}
	float time;
	float value;

	virtual int CompareTo( Object^ obj ) 
	{
     float_curve_pair^ temp = safe_cast<float_curve_pair^>(obj);

     return time.CompareTo(temp->time);
	}
};

public ref class float_curve_event_args:public EventArgs
{
public:
	float_curve_event_args(float_curve_pair^ set_key):
	  key(set_key){}

	float_curve_pair^ key;
};

[System::ComponentModel::EditorAttribute(float_curve_type_editor::typeid, System::Drawing::Design::UITypeEditor::typeid)]
public ref class float_curve
{
	float						m_min_value;
	float						m_max_value;
	float						m_min_time;
	float						m_max_time;
	bool						m_initialized_by_config;
	vostok::configs::lua_config_value*	m_curve_config;

	System::Collections::Generic::List<float_curve_pair^>^	m_container;
public:
	event EventHandler<float_curve_event_args^>^			key_added;
	event EventHandler<float_curve_event_args^>^			key_altered;
	event EventHandler<float_curve_event_args^>^			key_removed;
	event EventHandler^										keys_cleared;

				float_curve		();
				float_curve		(vostok::configs::lua_config_value const& curve_config);
				float_curve		(float set_min_time, float set_max_time, float set_min_value, float set_max_value);

private:
				~float_curve(){
					if (m_curve_config != nullptr)
						DELETE(m_curve_config);
				}
public:


	property float min_value{
		float	get()			{return m_min_value;}
		void	set(float v)	{m_min_value=v; if(m_min_value>m_max_value) m_min_value=m_max_value;}
	}
	property float max_value{
		float	get()			{return m_max_value;}
		void	set(float v)	{m_max_value=v; if(m_min_value>m_max_value) m_max_value=m_min_value;}
	}
	property float min_time{
		float	get()			{return m_min_time;}
		void	set(float v)	{m_min_time=v; if(m_min_time>m_max_time) m_min_time=m_max_time;}
	}
	property float max_time{
		float	get()			{return m_max_time;}
		void	set(float v)	{m_max_time=v; if(m_min_time>m_max_time) m_max_time=m_min_time;}
	}
	property configs::lua_config_value*	curve_config{
		configs::lua_config_value*		get(){return m_curve_config;}
	}

	void		add_key					(float time, float value);
	void		alter_key				(float_curve_pair^ key, float time, float value);
	void		remove_key				(int idx);
	void		clear_keys				();
	float		calc_value				(float time);
	void		synchronize_config		( );

	void		save(configs::lua_config_value& config);
	void		load(configs::lua_config_value& config);
	void		load_keys_from_config	(configs::lua_config_value const& keys_config);
	void		save_keys_to_config		(configs::lua_config_value& keys_config);


	void		draw(Drawing::Graphics^ g,System::Drawing::Pen^ pen, Drawing2D::Matrix^ matrix);

	property int count{
		int		get()	{return m_container->Count;}
	}

	property ReadOnlyCollection<float_curve_pair^>^ keys{
		ReadOnlyCollection<float_curve_pair^>^ get(){return m_container->AsReadOnly();}
	}

	property float_curve_pair^ key [int]{
		float_curve_pair^	get (int idx)	{return m_container[idx];}
	}
};

}; //namespace editor_base
}; //namespace vostok

#endif //#ifndef FLOAT_CURVE_H_INCLUDED