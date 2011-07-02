require 'rubygems'
require 'sinatra'

set :port, 4567
set :host, "localhost"
enable :sessions

get "/simple" do
  "Kukuryku!"
end

get "/simple.html" do
  "<html><body>Simple!</body></html>"
end

get "/simple.xml" do
  content_type 'application/xml'
  "<?xml version=\"1.0\"?><root>Simple!</root>"
end

get "/simple.txt" do
  content_type 'text/plain'
  "Simple!"
end

get "/xpath.xml" do
  content_type 'application/xml'
  "<?xml version=\"1.0\"?><root><elems><elem load='yes'>First</elem><elem>Second</elem><elem load='yes'>Third</elem></elems></root>"
end

get "/xpath.html" do
  "<html><body><ul id='elems'><li class='load foo'>First</li><li>Second</li><li class='load'>Third</li></ul></body></html>"
end

get "/anchors.html" do
  "<html><body><div>I am a link!</div><div>I am a div!</div><a href='#' name='link'>I am a link!</a><form><button id='buuu'>I am a button!</button><input type='submit' name='foo' value='I am a submit!' /></form></body></html>"
end

get "/fields.html" do
  "<html><body><form action='/'><input type='text' name='foo' /><input type='password' id='pass' /><label for='bar'>Hello label!</label><textarea id='bar'></textarea><input type='submit' id='opts' /><select id='opts'><option value='1'>Foo</option></select></form></body></html>";
end

get "/xml-elements.xml" do
  content_type 'application/xml'
  "<?xml version=\"1.0\"?><root><elem foo='bar'>Hello Foo!</elem><elem><sub>Hello</sub> sub!</elem></root>"
end

post "/simple" do
  "mike: #{params[:mike]}; foo: #{params[:foo]};"
end

get "/custom-headers" do
  "Accept: #{request.env["HTTP_ACCEPT"]}; Another: #{request.env["HTTP_ANOTHER"]};"
end

get "/follow-redirects" do
  redirect "/redirected"
end

get "/redirected" do
  "Redirected!"
end

get "/cookies/show" do
  "foo=#{request.cookies["foo"]}"
end

get "/cookies/set" do
  response.set_cookie "foo", "foobar"
  response.set_cookie "bar", "yeah!"
  "Want more cooookies!"
end

get "/iframes/1.html" do
  "<html><body>Iframe 1</body></html>"
end

get "/iframes/2.html" do
  "<html><body>Iframe 2</body></html>"
end

get "/iframes.html" do
  "<html><body><iframe src='/iframes/1.html'></iframe><iframe src='/iframes/2.html' name='foo'></iframe></body></html>"
end

get "/frameset.html" do
  "<html><frameset cols='50%,50%'><frame src='/iframes/1.html' /><frame src='/iframes/2.html' name='foo' /></frameset></html>"
end

get "/with-title.html" do
  "<html><head><title>Hello World!</title></head><body>Hello!</body></html>"
end
