require 'rubygems'
require 'sinatra'

set :port, 4567
set :host, "localhost"

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

get "/xpath.xml" do
  content_type 'application/xml'
  "<?xml version=\"1.0\"?><root><elems><elem load='yes'>First</elem><elem>Second</elem><elem load='yes'>Third</elem></elems></root>"
end

get "/xpath.html" do
  "<html><body><ul id='elems'><li class='load'>First</li><li>Second</li><li class='load'>Third</li></ul></body></html>"
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
