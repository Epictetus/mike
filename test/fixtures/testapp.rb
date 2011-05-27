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
