/************************************************************************************

 Authors     :   Bradley Austin Davis <bdavis@saintandreas.org>
 Copyright   :   Copyright Brad Davis. All Rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 ************************************************************************************/

#include "Common.h"

// This is a library for 3D mesh decompression
#include <openctmpp.h>

#ifdef HAVE_OPENCV

#include <opencv2/opencv.hpp>

#else

#include "IO.h"
#include <fstream>
#include <png.h>

#endif

using namespace gl;
using namespace std;

// Adapted (totally different from 'stolen') from OpenFrameworks
const glm::vec3 Colors::gray(1.0f / 2, 1.0f / 2, 1.0f / 2);
const glm::vec3 Colors::white(1.0f, 1.0f, 1.0f);
const glm::vec3 Colors::red(1.0f, 0, 0);
const glm::vec3 Colors::green(0, 1.0f, 0);
const glm::vec3 Colors::blue(0, 0, 1.0f);
const glm::vec3 Colors::cyan(0, 1.0f, 1.0f);
const glm::vec3 Colors::magenta(1.0f, 0, 1.0f);
const glm::vec3 Colors::yellow(1.0f, 1.0f, 0);
const glm::vec3 Colors::black(0, 0, 0);
const glm::vec3 Colors::aliceBlue(0.941176, 0.972549, 1);
const glm::vec3 Colors::antiqueWhite(0.980392, 0.921569, 0.843137);
const glm::vec3 Colors::aqua(0, 1, 1);
const glm::vec3 Colors::aquamarine(0.498039, 1, 0.831373);
const glm::vec3 Colors::azure(0.941176, 1, 1);
const glm::vec3 Colors::beige(0.960784, 0.960784, 0.862745);
const glm::vec3 Colors::bisque(1, 0.894118, 0.768627);
const glm::vec3 Colors::blanchedAlmond(1, 0.921569, 0.803922);
const glm::vec3 Colors::blueViolet(0.541176, 0.168627, 0.886275);
const glm::vec3 Colors::brown(0.647059, 0.164706, 0.164706);
const glm::vec3 Colors::burlyWood(0.870588, 0.721569, 0.529412);
const glm::vec3 Colors::cadetBlue(0.372549, 0.619608, 0.627451);
const glm::vec3 Colors::chartreuse(0.498039, 1, 0);
const glm::vec3 Colors::chocolate(0.823529, 0.411765, 0.117647);
const glm::vec3 Colors::coral(1, 0.498039, 0.313726);
const glm::vec3 Colors::cornflowerBlue(0.392157, 0.584314, 0.929412);
const glm::vec3 Colors::cornsilk(1, 0.972549, 0.862745);
const glm::vec3 Colors::crimson(0.862745, 0.0784314, 0.235294);
const glm::vec3 Colors::darkBlue(0, 0, 0.545098);
const glm::vec3 Colors::darkCyan(0, 0.545098, 0.545098);
const glm::vec3 Colors::darkGoldenRod(0.721569, 0.52549, 0.0431373);
const glm::vec3 Colors::darkGray(0.662745, 0.662745, 0.662745);
const glm::vec3 Colors::darkGrey(0.662745, 0.662745, 0.662745);
const glm::vec3 Colors::darkGreen(0, 0.392157, 0);
const glm::vec3 Colors::darkKhaki(0.741176, 0.717647, 0.419608);
const glm::vec3 Colors::darkMagenta(0.545098, 0, 0.545098);
const glm::vec3 Colors::darkOliveGreen(0.333333, 0.419608, 0.184314);
const glm::vec3 Colors::darkorange(1, 0.54902, 0);
const glm::vec3 Colors::darkOrchid(0.6, 0.196078, 0.8);
const glm::vec3 Colors::darkRed(0.545098, 0, 0);
const glm::vec3 Colors::darkSalmon(0.913725, 0.588235, 0.478431);
const glm::vec3 Colors::darkSeaGreen(0.560784, 0.737255, 0.560784);
const glm::vec3 Colors::darkSlateBlue(0.282353, 0.239216, 0.545098);
const glm::vec3 Colors::darkSlateGray(0.184314, 0.309804, 0.309804);
const glm::vec3 Colors::darkSlateGrey(0.184314, 0.309804, 0.309804);
const glm::vec3 Colors::darkTurquoise(0, 0.807843, 0.819608);
const glm::vec3 Colors::darkViolet(0.580392, 0, 0.827451);
const glm::vec3 Colors::deepPink(1, 0.0784314, 0.576471);
const glm::vec3 Colors::deepSkyBlue(0, 0.74902, 1);
const glm::vec3 Colors::dimGray(0.411765, 0.411765, 0.411765);
const glm::vec3 Colors::dimGrey(0.411765, 0.411765, 0.411765);
const glm::vec3 Colors::dodgerBlue(0.117647, 0.564706, 1);
const glm::vec3 Colors::fireBrick(0.698039, 0.133333, 0.133333);
const glm::vec3 Colors::floralWhite(1, 0.980392, 0.941176);
const glm::vec3 Colors::forestGreen(0.133333, 0.545098, 0.133333);
const glm::vec3 Colors::fuchsia(1, 0, 1);
const glm::vec3 Colors::gainsboro(0.862745, 0.862745, 0.862745);
const glm::vec3 Colors::ghostWhite(0.972549, 0.972549, 1);
const glm::vec3 Colors::gold(1, 0.843137, 0);
const glm::vec3 Colors::goldenRod(0.854902, 0.647059, 0.12549);
const glm::vec3 Colors::grey(0.501961, 0.501961, 0.501961);
const glm::vec3 Colors::greenYellow(0.678431, 1, 0.184314);
const glm::vec3 Colors::honeyDew(0.941176, 1, 0.941176);
const glm::vec3 Colors::hotPink(1, 0.411765, 0.705882);
const glm::vec3 Colors::indianRed(0.803922, 0.360784, 0.360784);
const glm::vec3 Colors::indigo(0.294118, 0, 0.509804);
const glm::vec3 Colors::ivory(1, 1, 0.941176);
const glm::vec3 Colors::khaki(0.941176, 0.901961, 0.54902);
const glm::vec3 Colors::lavender(0.901961, 0.901961, 0.980392);
const glm::vec3 Colors::lavenderBlush(1, 0.941176, 0.960784);
const glm::vec3 Colors::lawnGreen(0.486275, 0.988235, 0);
const glm::vec3 Colors::lemonChiffon(1, 0.980392, 0.803922);
const glm::vec3 Colors::lightBlue(0.678431, 0.847059, 0.901961);
const glm::vec3 Colors::lightCoral(0.941176, 0.501961, 0.501961);
const glm::vec3 Colors::lightCyan(0.878431, 1, 1);
const glm::vec3 Colors::lightGoldenRodYellow(0.980392, 0.980392, 0.823529);
const glm::vec3 Colors::lightGray(0.827451, 0.827451, 0.827451);
const glm::vec3 Colors::lightGrey(0.827451, 0.827451, 0.827451);
const glm::vec3 Colors::lightGreen(0.564706, 0.933333, 0.564706);
const glm::vec3 Colors::lightPink(1, 0.713726, 0.756863);
const glm::vec3 Colors::lightSalmon(1, 0.627451, 0.478431);
const glm::vec3 Colors::lightSeaGreen(0.12549, 0.698039, 0.666667);
const glm::vec3 Colors::lightSkyBlue(0.529412, 0.807843, 0.980392);
const glm::vec3 Colors::lightSlateGray(0.466667, 0.533333, 0.6);
const glm::vec3 Colors::lightSlateGrey(0.466667, 0.533333, 0.6);
const glm::vec3 Colors::lightSteelBlue(0.690196, 0.768627, 0.870588);
const glm::vec3 Colors::lightYellow(1, 1, 0.878431);
const glm::vec3 Colors::lime(0, 1, 0);
const glm::vec3 Colors::limeGreen(0.196078, 0.803922, 0.196078);
const glm::vec3 Colors::linen(0.980392, 0.941176, 0.901961);
const glm::vec3 Colors::maroon(0.501961, 0, 0);
const glm::vec3 Colors::mediumAquaMarine(0.4, 0.803922, 0.666667);
const glm::vec3 Colors::mediumBlue(0, 0, 0.803922);
const glm::vec3 Colors::mediumOrchid(0.729412, 0.333333, 0.827451);
const glm::vec3 Colors::mediumPurple(0.576471, 0.439216, 0.858824);
const glm::vec3 Colors::mediumSeaGreen(0.235294, 0.701961, 0.443137);
const glm::vec3 Colors::mediumSlateBlue(0.482353, 0.407843, 0.933333);
const glm::vec3 Colors::mediumSpringGreen(0, 0.980392, 0.603922);
const glm::vec3 Colors::mediumTurquoise(0.282353, 0.819608, 0.8);
const glm::vec3 Colors::mediumVioletRed(0.780392, 0.0823529, 0.521569);
const glm::vec3 Colors::midnightBlue(0.0980392, 0.0980392, 0.439216);
const glm::vec3 Colors::mintCream(0.960784, 1, 0.980392);
const glm::vec3 Colors::mistyRose(1, 0.894118, 0.882353);
const glm::vec3 Colors::moccasin(1, 0.894118, 0.709804);
const glm::vec3 Colors::navajoWhite(1, 0.870588, 0.678431);
const glm::vec3 Colors::navy(0, 0, 0.501961);
const glm::vec3 Colors::oldLace(0.992157, 0.960784, 0.901961);
const glm::vec3 Colors::olive(0.501961, 0.501961, 0);
const glm::vec3 Colors::oliveDrab(0.419608, 0.556863, 0.137255);
const glm::vec3 Colors::orange(1, 0.647059, 0);
const glm::vec3 Colors::orangeRed(1, 0.270588, 0);
const glm::vec3 Colors::orchid(0.854902, 0.439216, 0.839216);
const glm::vec3 Colors::paleGoldenRod(0.933333, 0.909804, 0.666667);
const glm::vec3 Colors::paleGreen(0.596078, 0.984314, 0.596078);
const glm::vec3 Colors::paleTurquoise(0.686275, 0.933333, 0.933333);
const glm::vec3 Colors::paleVioletRed(0.858824, 0.439216, 0.576471);
const glm::vec3 Colors::papayaWhip(1, 0.937255, 0.835294);
const glm::vec3 Colors::peachPuff(1, 0.854902, 0.72549);
const glm::vec3 Colors::peru(0.803922, 0.521569, 0.247059);
const glm::vec3 Colors::pink(1, 0.752941, 0.796078);
const glm::vec3 Colors::plum(0.866667, 0.627451, 0.866667);
const glm::vec3 Colors::powderBlue(0.690196, 0.878431, 0.901961);
const glm::vec3 Colors::purple(0.501961, 0, 0.501961);
const glm::vec3 Colors::rosyBrown(0.737255, 0.560784, 0.560784);
const glm::vec3 Colors::royalBlue(0.254902, 0.411765, 0.882353);
const glm::vec3 Colors::saddleBrown(0.545098, 0.270588, 0.0745098);
const glm::vec3 Colors::salmon(0.980392, 0.501961, 0.447059);
const glm::vec3 Colors::sandyBrown(0.956863, 0.643137, 0.376471);
const glm::vec3 Colors::seaGreen(0.180392, 0.545098, 0.341176);
const glm::vec3 Colors::seaShell(1, 0.960784, 0.933333);
const glm::vec3 Colors::sienna(0.627451, 0.321569, 0.176471);
const glm::vec3 Colors::silver(0.752941, 0.752941, 0.752941);
const glm::vec3 Colors::skyBlue(0.529412, 0.807843, 0.921569);
const glm::vec3 Colors::slateBlue(0.415686, 0.352941, 0.803922);
const glm::vec3 Colors::slateGray(0.439216, 0.501961, 0.564706);
const glm::vec3 Colors::slateGrey(0.439216, 0.501961, 0.564706);
const glm::vec3 Colors::snow(1, 0.980392, 0.980392);
const glm::vec3 Colors::springGreen(0, 1, 0.498039);
const glm::vec3 Colors::steelBlue(0.27451, 0.509804, 0.705882);
const glm::vec3 Colors::blueSteel(0.27451, 0.509804, 0.705882);
const glm::vec3 Colors::tan(0.823529, 0.705882, 0.54902);
const glm::vec3 Colors::teal(0, 0.501961, 0.501961);
const glm::vec3 Colors::thistle(0.847059, 0.74902, 0.847059);
const glm::vec3 Colors::tomato(1, 0.388235, 0.278431);
const glm::vec3 Colors::turquoise(0.25098, 0.878431, 0.815686);
const glm::vec3 Colors::violet(0.933333, 0.509804, 0.933333);
const glm::vec3 Colors::wheat(0.960784, 0.870588, 0.701961);
const glm::vec3 Colors::whiteSmoke(0.960784, 0.960784, 0.960784);
const glm::vec3 Colors::yellowGreen(0.603922, 0.803922, 0.196078);

// Some defines to make calculations below more transparent
#define TRIANGLES_PER_FACE 2
#define VERTICES_PER_TRIANGLE 3
#define VERTICES_PER_EDGE 2
#define FLOATS_PER_VERTEX 3

#define CUBE_SIZE 1.0f
#define CUBE_P (CUBE_SIZE / 2.0f)
#define CUBE_N (-1.0f * CUBE_P)

// Cube geometry
#define CUBE_VERT_COUNT 8
#define CUBE_FACE_COUNT 6
#define CUBE_EDGE_COUNT 12
#define CUBE_INDEX_COUNT (CUBE_FACE_COUNT * \
  TRIANGLES_PER_FACE * VERTICES_PER_TRIANGLE)

// Vertices for a unit cube centered at the origin
const glm::vec4 CUBE_VERTICES[CUBE_VERT_COUNT] = { //
    glm::vec4(CUBE_N, CUBE_N, CUBE_P, 1), // ll 0
    glm::vec4(CUBE_P, CUBE_N, CUBE_P, 1), // lr 1
    glm::vec4(CUBE_N, CUBE_P, CUBE_P, 1), // ul 2
    glm::vec4(CUBE_P, CUBE_P, CUBE_P, 1), // ur 3

    glm::vec4(CUBE_N, CUBE_N, CUBE_N, 1), // ll 4
    glm::vec4(CUBE_P, CUBE_N, CUBE_N, 1), // lr 5
    glm::vec4(CUBE_N, CUBE_P, CUBE_N, 1), // ul 6
    glm::vec4(CUBE_P, CUBE_P, CUBE_N, 1), // ur 7
};

const glm::vec3 CUBE_FACE_COLORS[] = { //
    Colors::red, Colors::green, Colors::blue, Colors::yellow, Colors::cyan,
        Colors::magenta, };

// 6 sides * 2 triangles * 3 vertices
const GLuint CUBE_INDICES[
CUBE_FACE_COUNT * TRIANGLES_PER_FACE * VERTICES_PER_TRIANGLE] = { //
    0, 1, 2, 2, 1, 3, // X Positive
    2, 3, 6, 6, 3, 7, // X Negative
    6, 7, 4, 4, 7, 5, // Y Positive
    7, 3, 5, 5, 3, 1, // Y Negative
    5, 1, 4, 4, 1, 0, // Z Positive
    4, 0, 6, 6, 0, 2, // Z Negative
};

const unsigned int CUBE_WIRE_INDICES[CUBE_EDGE_COUNT * VERTICES_PER_EDGE] =
    { //
    0, 1, 1, 2, 2, 3, 3, 0, // square
        4, 5, 5, 6, 6, 7, 7, 4, // facing square
        0, 4, 1, 5, 2, 6, 3, 7, // transverse lines
    };

//
//// Mirror Z style
//const glm::vec3 QUAD_VERTICES[4] = { //
//  glm::vec3(-1, -1, 0),
//  glm::vec3(+1, -1, 0),
//  glm::vec3(-1, +1, 0),
//  glm::vec3(+1, +1, 0),
//};
//
//// Triangle strip
//const GLuint QUAD_INDICES[4] = { //
//    0, 1, 2, 3
//};

const glm::vec3 GlUtils::X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 GlUtils::Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 GlUtils::Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 GlUtils::ORIGIN = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 GlUtils::UP = glm::vec3(0.0f, 1.0f, 0.0f);

//VertexBufferPtr GlUtils::getQuadVertices() {
//  VertexBufferPtr result(new VertexBuffer());
//  // Create the buffers for the texture quad we will draw
//  result->bind();
//  (*result) << gl::makeArrayLoader(QUAD_VERTICES);
//  result->unbind();
//  GL_CHECK_ERROR;
//  return result;
//}
//
//IndexBufferPtr GlUtils::getQuadIndices() {
//  IndexBufferPtr result(new IndexBuffer());
//  result->bind();
//  (*result) << gl::makeArrayLoader(QUAD_INDICES);
//  result->unbind();
//  GL_CHECK_ERROR;
//  return result;
//}
//
VertexBufferPtr getCubeVertices() {
  VertexBufferPtr result(new VertexBuffer());
  // Create the buffers for the texture quad we will draw
  result->bind();
  GL_CHECK_ERROR;
  (*result) << gl::makeArrayLoader(CUBE_VERTICES);
  GL_CHECK_ERROR;
  result->unbind();
  GL_CHECK_ERROR;
  return result;
}

IndexBufferPtr getCubeIndices() {
  IndexBufferPtr result(new IndexBuffer());
  result->bind();
  (*result) << gl::makeArrayLoader(CUBE_INDICES);
  result->unbind();
  GL_CHECK_ERROR;
  return result;
}

IndexBufferPtr getCubeWireIndices() {
  IndexBufferPtr result(new IndexBuffer());
  result->bind();
  (*result) << gl::makeArrayLoader(CUBE_WIRE_INDICES);
  result->unbind();
  GL_CHECK_ERROR;
  return result;
}

void GlUtils::tumble(const glm::vec3 & camera) {
  static const float Y_ROTATION_RATE = 0.01f;
  static const float Z_ROTATION_RATE = 0.05f;
  glm::mat4 & modelview = gl::Stacks::modelview().top();
  modelview = glm::lookAt(camera, ORIGIN, UP);
  modelview = glm::rotate(modelview,
      Platform::elapsedMillis() * Y_ROTATION_RATE, GlUtils::Y_AXIS);
  modelview = glm::rotate(modelview,
      Platform::elapsedMillis() * Z_ROTATION_RATE, GlUtils::Z_AXIS);
}

//    void ArtificialHorizon::customDraw() {
//        ofPushMatrix();
//            ofRotateX(90);
//            ofSetColor(255, 100, 0);
//            hemi.draw();
//            ofSetColor(20);
//            ofTranslate(0, 0, 1.02);
//            ofCircle(0, 0, 0.25);
//        ofPopMatrix();
//
//        ofPushMatrix();
//            ofRotateX(-90);
//            ofSetColor(100, 100, 255);
//            hemi.draw();
//            ofSetColor(20);
//            ofTranslate(0, 0, 1.02);
//            ofCircle(0, 0, 0.25);
//        ofPopMatrix();
//
//        ofSetColor(20);
//
//        ofPushMatrix();
//            ofTranslate(0, 0, 1.02);
//            ofRect(-0.50, -0.02, 1.0, 0.04);
//        ofPopMatrix();

void GlUtils::renderGeometry(
    const GeometryPtr & geometry,
    gl::ProgramPtr program) {
  program->use();
  Stacks::lights().apply(program);
  Stacks::projection().apply(program);
  Stacks::modelview().apply(program);
  geometry->bindVertexArray();
  geometry->draw();

  VertexArray::unbind();
  Program::clear();
}

void GlUtils::renderBunny() {
  static GeometryPtr bunnyGeometry =
      getMesh(Resource::MESHES_BUNNY2_CTM).getGeometry();
  ProgramPtr program = GlUtils::getProgram(
      Resource::SHADERS_LITCOLORED_VS,
      Resource::SHADERS_LITCOLORED_FS);
  program->use();
  program->setUniform("Color", glm::vec4(1));
  renderGeometry(bunnyGeometry, program);
}

gl::GeometryPtr GlUtils::getQuadGeometry(const glm::vec2 & min,
    const glm::vec2 & max, const glm::vec2 & texMin,
    const glm::vec2 & texMax) {
  std::vector<glm::vec4> v;
  v.push_back(glm::vec4(min.x, min.y, 0, 1));
  v.push_back(glm::vec4(texMin.x, texMin.y, 0, 0));
  v.push_back(glm::vec4(max.x, min.y, 0, 1));
  v.push_back(glm::vec4(texMax.x, texMin.y, 0, 1));
  v.push_back(glm::vec4(min.x, max.y, 0, 1));
  v.push_back(glm::vec4(texMin.x, texMax.y, 0, 1));
  v.push_back(glm::vec4(max.x, max.y, 0, 1));
  v.push_back(glm::vec4(texMax.x, texMax.y, 0, 1));

  std::vector<GLuint> i;
  i.push_back(0);
  i.push_back(1);
  i.push_back(2);
  i.push_back(3);
  i.push_back(2);
  i.push_back(1);
  i.push_back(3);
  return gl::GeometryPtr(new gl::Geometry(
      v, i, 2,
      // Buffer has texture coordinates
      gl::Geometry::Flag::HAS_TEXTURE,
      // Indices are for a triangle strip
      GL_TRIANGLES));
}

#ifdef HAVE_OPENCV

template<GLenum TargetType = GL_TEXTURE_2D>
void readPngToTexture(const void * data, size_t size,
    std::shared_ptr<gl::Texture<TargetType> > & texture, glm::vec2 & textureSize) {
  std::vector<unsigned char> v(size);
  memcpy(&(v[0]), data, size);
  cv::Mat image = cv::imdecode(v, CV_LOAD_IMAGE_ANYDEPTH);
  texture = std::shared_ptr<gl::Texture<TargetType> >(new gl::Texture<TargetType>());
  GL_CHECK_ERROR;
  texture->bind();
  GL_CHECK_ERROR;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, image.cols, image.rows, 0, GL_RGB,
  GL_UNSIGNED_BYTE, image.data);
  GL_CHECK_ERROR;
  gl::Texture<TargetType>::unbind();
  GL_CHECK_ERROR;
  }


//void GlUtils::loadImageToBoundTexture(const std::string & file, glm::ivec2 & outSize, GLenum target) {
//  cv::Mat image = cv::imread(file, CV_LOAD_IMAGE_COLOR);
//  // OpenCV uses upper left as the origin for the image data.  OpenGL
//  // uses lower left, so we need to flip the image vertically before
//  // we hand it to OpenGL
//  cv::flip(image, image, 0);
//  cv::cvtColor(image, image, CV_BGR2RGB);
//  outSize.x = image.cols;
//  outSize.y = image.rows;
//  glTexImage2D(target, 0, GL_RGBA8, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data);
//}

void getOpenCvImageData(cv::Mat & image, glm::ivec2 & outSize, std::vector<unsigned char> & outData) {
  // OpenCV uses upper left as the origin for the image data.  OpenGL
  // uses lower left, so we need to flip the image vertically before
  // we hand it to OpenGL
  cv::flip(image, image, 0);
  cv::cvtColor(image, image, CV_BGR2RGB);
  outSize.x = image.cols;
  outSize.y = image.rows;
  size_t byteCount = image.dataend - image.datastart;
  outData.resize(byteCount);
  memcpy(&outData[0], image.data, byteCount);
}

void GlUtils::getImageData(
    const std::string & file,
    glm::ivec2 & outSize,
    std::vector<unsigned char> & outData,
    bool flip
) {
  cv::Mat image = cv::imread(file, CV_LOAD_IMAGE_COLOR);
  getOpenCvImageData(image, outSize, outData);
}

void GlUtils::getImageData(
  const std::vector<unsigned char> & indata,
  glm::ivec2 & outSize,
  std::vector<unsigned char> & outData,
  bool flip
) {
  cv::Mat image = cv::imdecode(indata, CV_LOAD_IMAGE_COLOR);
  getOpenCvImageData(image, outSize, outData);
}

void GlUtils::getImageData(
  std::istream & in,
  glm::ivec2 & outSize,
  std::vector<unsigned char> & outData,
  bool flip
) {
  // FIXME
}

#else

void PngDataCallback(png_structp png_ptr, png_bytep outBytes,
    png_size_t byteCountToRead) {
  istream * pIn = (istream*) png_get_io_ptr(png_ptr);
  if (pIn == nullptr)
    throw runtime_error("PNG: missing stream pointer");

  istream & in = *pIn; // png_ptr->io_ptr;
  const ios::pos_type start = in.tellg();
  readStream(in, outBytes, byteCountToRead);
  const ios::pos_type bytesRead = in.tellg() - start;
  if ((png_size_t) bytesRead != byteCountToRead)
    throw runtime_error("PNG: short read");
}

void GlUtils::getImageData(
    istream & in,
    glm::ivec2 & outSize,
    std::vector<unsigned char> & outData,
    bool flip
) {
  enum {
    kPngSignatureLength = 8
  };
  uint8_t pngSignature[kPngSignatureLength];
  readStream(in, pngSignature);
  if (!png_check_sig(pngSignature, kPngSignatureLength))
    throw runtime_error("bad png sig");

  // get PNG file info struct (memory is allocated by libpng)
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
    NULL, NULL);
  if (png_ptr == nullptr)
    throw runtime_error("PNG: bad signature");

  // get PNG image data info struct (memory is allocated by libpng)
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == nullptr) {
    // libpng must free file info struct memory before we bail
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    throw runtime_error("PNG: failed to allocate header");
  }

  png_set_read_fn(png_ptr, &in, PngDataCallback);
  png_set_sig_bytes(png_ptr, kPngSignatureLength);
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_STRIP_ALPHA | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

  png_uint_32 width = 0;
  png_uint_32 height = 0;
  int colorType = -1;
  int bitDepth = 0;
  ::uint32_t retval = png_get_IHDR(png_ptr, info_ptr, &width, &height,
    &bitDepth, &colorType, nullptr, nullptr, nullptr);

  if (retval != 1) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    throw runtime_error("PNG: failed to read header");
  }

  outSize.x = width;
  outSize.y = height;

  const ::uint32_t bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
  outData.resize(bytesPerRow * height);
  ::uint8_t * textureData = &outData[0];

  png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
  for (::uint32_t rowIdx = 0; rowIdx < height; ++rowIdx) {
    size_t offset = flip ? (height - (rowIdx + 1)) : rowIdx;
    offset *= bytesPerRow;
    memcpy(textureData + offset, row_pointers[rowIdx], bytesPerRow);
  }

  GLenum source_type;
  switch (colorType) {
  case PNG_COLOR_TYPE_RGB:
    source_type = GL_RGB;
    break;
  case PNG_COLOR_TYPE_RGB_ALPHA:
    source_type = GL_RGBA;
    break;
  case PNG_COLOR_TYPE_GRAY:
    source_type = GL_LUMINANCE;
    break;

  default:
    FAIL("Unable to parse PNG color type %d", colorType);
  }
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
}

void GlUtils::getImageData(
  const std::vector<unsigned char> & indata,
  glm::ivec2 & outSize,
  std::vector<unsigned char> & outData,
  bool flip
) {
  std::istringstream in(std::string((const char*)&indata[0], indata.size()));
  getImageData(in, outSize, outData, flip);
}

void GlUtils::getImageData(
  Resource resource,
  glm::ivec2 & outSize,
  std::vector<unsigned char> & outData,
  bool flip
  ) {
  std::istringstream in(Platform::getResourceData(resource));
  getImageData(in, outSize, outData, flip);
}

#endif


#define EPSILON 0.002

void GlUtils::renderArtificialHorizon(float alpha) {
  static GeometryPtr geometry;
  if (!geometry) {
    Mesh mesh;
    MatrixStack & m = mesh.getModel();

    m.push();
    {
      m.top() = glm::translate(glm::mat4(), glm::vec3(0, 0, 1.01));
      mesh.getColor() = Colors::yellow;
      mesh.addQuad(0.5, 0.05f);
      mesh.fillColors(true);
      mesh.getColor() = Colors::lightGray;
      glm::vec2 bar(0.5, 0.025);
      glm::vec2 smallBar(0.3, 0.015);
      for (int i = 1; i <= 4; ++i) {
        float angle = i * 20.0f;
        m.identity().rotate(angle, GlUtils::X_AXIS).translate(
            GlUtils::Z_AXIS);
        mesh.addQuad(bar);
        m.identity().rotate(180.0f, GlUtils::Y_AXIS).rotate(angle,
            GlUtils::X_AXIS).translate(GlUtils::Z_AXIS);
        mesh.addQuad(bar);
        m.identity().rotate(180.0f, GlUtils::Z_AXIS).rotate(angle,
            GlUtils::X_AXIS).translate(GlUtils::Z_AXIS);
        mesh.addQuad(bar);
        m.identity().rotate(180.0f, GlUtils::Z_AXIS).rotate(180.0f,
            GlUtils::Y_AXIS).rotate(angle, GlUtils::X_AXIS).translate(
            GlUtils::Z_AXIS);
        mesh.addQuad(bar);

        angle -= 10.0f;
        m.identity().rotate(angle, GlUtils::X_AXIS).translate(
            GlUtils::Z_AXIS);
        mesh.addQuad(smallBar);
        m.identity().rotate(180.0f, GlUtils::Y_AXIS).rotate(angle,
            GlUtils::X_AXIS).translate(GlUtils::Z_AXIS);
        mesh.addQuad(smallBar);
        m.identity().rotate(180.0f, GlUtils::Z_AXIS).rotate(angle,
            GlUtils::X_AXIS).translate(GlUtils::Z_AXIS);
        mesh.addQuad(smallBar);
        m.identity().rotate(180.0f, GlUtils::Z_AXIS).rotate(180.0f,
            GlUtils::Y_AXIS).rotate(angle, GlUtils::X_AXIS).translate(
            GlUtils::Z_AXIS);
        mesh.addQuad(smallBar);
      }
    }
    m.pop();
    mesh.fillNormals(true);

    const Mesh & hemi = getMesh(Resource::MESHES_HEMI_CTM);
    m.top() = glm::rotate(glm::mat4(), -90.0f, GlUtils::X_AXIS);
    mesh.getColor() = Colors::cyan;
    mesh.addMesh(hemi, true);

    m.top() = glm::rotate(glm::mat4(), 90.0f, GlUtils::X_AXIS);
    mesh.getColor() = Colors::orange;
    mesh.addMesh(hemi);
    {
      set<int> poleIndices;
      for (int i = 0; i < mesh.positions.size(); ++i) {
        const glm::vec3 & v = mesh.positions[i];
        if (abs(v.x) < EPSILON && abs(v.z) < EPSILON) {
          poleIndices.insert(i);
        }
      }
      for (int i = 0; i < mesh.indices.size(); i += 3) {
        bool black = false;
        for (int j = i; j < i + 3; ++j) {
          if (poleIndices.count(mesh.indices[j])) {
            black = true;
            break;
          }
        }
        if (black) {
          for (int j = i; j < i + 3; ++j) {
            mesh.colors[mesh.indices[j]] = Colors::grey;
          }
        }
      }
    }
    geometry = mesh.getGeometry();
  }
  ProgramPtr program = getProgram(
      Resource::SHADERS_LITCOLORED_VS,
      Resource::SHADERS_LITCOLORED_FS);
  program->use();
  program->setUniform("ForceAlpha", alpha);
  renderGeometry(geometry, program);
}

void GlUtils::renderRift() {
  static gl::GeometryPtr geometry;
  if (!geometry) {
    Mesh mesh;
    mesh.getModel().rotate(-107.0f, GlUtils::X_AXIS).scale(0.5f);
    const Mesh & sourceMesh = GlUtils::getMesh(Resource::MESHES_RIFT_CTM);
    mesh.addMesh(sourceMesh);
    geometry = mesh.getGeometry();
  }
  ProgramPtr program = getProgram(
      Resource::SHADERS_LIT_VS,
      Resource::SHADERS_LIT_FS);
  GlUtils::renderGeometry(geometry, program);
}


void GlUtils::drawQuad(const glm::vec2 & min, const glm::vec2 & max) {
  glBegin(GL_QUADS);
  glVertex2f(min.x, min.y);
  glVertex2f(max.x, min.y);
  glVertex2f(max.x, max.y);
  glVertex2f(min.x, max.y);
  glEnd();
}

void GlUtils::drawColorCube() {
  // These hold the vertices, indices and the binding between the
  // Shader variable names and the values loaded into video memory
  static GeometryPtr cubeGeometry(
      new Geometry(getCubeVertices(), getCubeIndices(),
      CUBE_FACE_COUNT * TRIANGLES_PER_FACE, 0));
  static GeometryPtr cubeWireGeometry(
      new Geometry(getCubeVertices(), getCubeWireIndices(),
      CUBE_EDGE_COUNT * VERTICES_PER_EDGE, 0));

  gl::Program & renderProgram = *GlUtils::getProgram(
      Resource::SHADERS_SIMPLE_VS, Resource::SHADERS_SIMPLE_FS);
  renderProgram.use();
  renderProgram.setUniform("Time", (float)Platform::elapsedMillis() / 1000.0f);
  // Load the projection and modelview matrices into the program
  Stacks::projection().apply(renderProgram);
  Stacks::modelview().apply(renderProgram);

  // Draw the cube faces, two calls for each face in order to set
  // the color and then draw the geometry
  cubeGeometry->bindVertexArray();
//  for (uintptr_t i = 0; i < CUBE_FACE_COUNT; ++i) {
//    renderProgram.setUniform4f("Color", glm::vec4(CUBE_FACE_COLORS[i], 1));
//    glDrawElements(GL_TRIANGLES,
//    TRIANGLES_PER_FACE * VERTICES_PER_TRIANGLE,
//    GL_UNSIGNED_INT, (void*) (i * 6 * 4));
//  }
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  for (uintptr_t i = 0; i < CUBE_FACE_COUNT; ++i) {
    renderProgram.setUniform4f("Color", glm::vec4(CUBE_FACE_COLORS[i], 1));
    glDrawElements(GL_TRIANGLES,
    TRIANGLES_PER_FACE * VERTICES_PER_TRIANGLE,
    GL_UNSIGNED_INT, (void*) (i * 6 * 4));
  }
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  VertexArray::unbind();

  // Now scale the modelview matrix slightly, so we can draw the cube outline
  // The apply method copies the top value into the shader, so we don't need to
  // keep the stack pushed while we render
//  Stacks::modelview().push().scale(1.01f).apply(renderProgram).pop();
  // Drawing a white wireframe around the cube
//  renderProgram.setUniform4f("Color", glm::vec4(Colors::white, 1));
//  cubeWireGeometry->bindVertexArray();
//  glDrawElements(GL_LINES, CUBE_EDGE_COUNT * VERTICES_PER_EDGE,
//  GL_UNSIGNED_INT, (void*) 0);
//  VertexArray::unbind();

  glUseProgram(0);
}

void GlUtils::drawAngleTicks() {
// Only necessary if you're using the fixed function pipeline
// Fix the modelview at exactly 1 unit away from the origin, no rotation
//  gl::Stacks::modelview().push(glm::mat4(1)).translate(glm::vec3(0, 0, -1));
//  glMatrixMode(GL_MODELVIEW);
//  glLoadMatrixf(glm::value_ptr(gl::Stacks::modelview().top()));
//  glMatrixMode(GL_PROJECTION);
//  glLoadMatrixf(glm::value_ptr(gl::Stacks::projection().top()));
//
//  float offsets[] = { //
//      (float) tan( PI / 6.0f), // 30 degrees
//      (float) tan( PI / 4.0f), // 45 degrees
//      (float) tan( PI / 3.0f) // 60 degrees
//      };
// 43.9 degrees puts tick on the inner edge of the screen
//           tan( PI / 4.22f ), // 42.6 degrees is the effective fov for wide screen
//                             // 43.9 degrees puts tick on the inner edge of the screen

//  glLineWidth(4.0);
//  glBegin(GL_LINES);
//  glColor3f(1, 1, 1);
//  gl::vertex(glm::vec3(-2, 0, 0));
//  gl::vertex(glm::vec3(2, 0, 0));
//  gl::vertex(glm::vec3(0, -2, 0));
//  gl::vertex(glm::vec3(0, 2, 0));
//
//// By keeping the camera locked at 1 unit away from the origin, all our
//// distances can be computer as tan(angle)
//  for (float offset : offsets) {
//    glColor3f(0, 1, 1);
//  gl::vertex(glm::vec3(offset, -0.05, 0));
//  gl::vertex(glm::vec3(offset, 0.05, 0));
//  gl::vertex(glm::vec3(-offset, -0.05, 0));
//  gl::vertex(glm::vec3(-offset, 0.05, 0));
//  }
//  for (float offset : offsets) {
//    glColor3f(0, 1, 1);
//  gl::vertex(glm::vec3(-0.05, offset, 0));
//  gl::vertex(glm::vec3(0.05, offset, 0));
//  gl::vertex(glm::vec3(-0.05, -offset, 0));
//  gl::vertex(glm::vec3(0.05, -offset, 0));
//  }
//  glEnd();
//  gl::Stacks::modelview().pop();
}

void GlUtils::draw3dGrid() {
  using namespace gl;

  GL_CHECK_ERROR;
  static GeometryPtr g;
  if (!g) {
    Mesh m;
    for (int i = 0; i < 5; ++i) {
      float offset = ((float) i * 0.2f) + 0.2f;
      glm::vec3 zOffset(0, 0, offset);
      glm::vec3 xOffset(offset, 0, 0);
      m.addVertex(-X_AXIS + zOffset);
      m.addVertex(X_AXIS + zOffset);
      m.addVertex(-X_AXIS - zOffset);
      m.addVertex(X_AXIS - zOffset);
      m.addVertex(-Z_AXIS + xOffset);
      m.addVertex(Z_AXIS + xOffset);
      m.addVertex(-Z_AXIS - xOffset);
      m.addVertex(Z_AXIS - xOffset);
    }
    m.addVertex(X_AXIS);
    m.addVertex(-X_AXIS);
    m.addVertex(Z_AXIS);
    m.addVertex(-Z_AXIS);
    g = m.getGeometry(GL_LINES);
  }
  ProgramPtr program = getProgram(Resource::SHADERS_SIMPLE_VS, Resource::SHADERS_SIMPLE_FS);
  GL_CHECK_ERROR;
  program->use();
  GL_CHECK_ERROR;
  program->setUniform("Color", glm::vec4(Colors::gray,1));
  GL_CHECK_ERROR;
  renderGeometry(g, program);
  GL_CHECK_ERROR;
}

//void GlUtils::drawOrigin() {
//  lineWidth(1.0);
//  begin(LINES);
//    color(vec3(0.25));
//    color(X_AXIS / 1.5f);
//    vertex(vec3(0));
//    vertex(X_AXIS);
//    color(Y_AXIS / 1.5f);
//    vertex(vec3(0));
//    vertex(Y_AXIS);
//    color(Z_AXIS / 1.5f);
//    vertex(vec3(0));
//    vertex(Z_AXIS);
//  end();
//}
//

namespace gl {
  void color(const glm::vec3 & color) {
    glColor3f(color.r, color.g, color.b);
  }
  void vertex(const glm::vec3 & v) {
    glVertex3f(v.x, v.y, v.z);
  }

  template <size_t SIZE>
  void vertices(glm::vec3 vs[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
      vertex(vs[i]);
    }
  }
}
//  vertex(glm::vec3(0));


void GlUtils::draw3dVector(glm::vec3 vec, const glm::vec3 & col) {

  Mesh m;
  m.color = Colors::gray;

  m.addVertex(glm::vec3());
  m.addVertex(glm::vec3(vec.x, 0, vec.z));

  m.addVertex(glm::vec3(vec.x, 0, vec.z));
  m.addVertex(vec);

  m.fillColors(true);
  m.color = col;
  m.addVertex(vec);
  m.addVertex(glm::vec3());

  m.fillColors();
  GeometryPtr g = m.getGeometry(GL_LINES);

  ProgramPtr program = getProgram(
      Resource::SHADERS_SIMPLECOLORED_VS,
      Resource::SHADERS_SIMPLE_FS);
  program->use();
  renderGeometry(g, program);
  gl::Program::clear();


//  lineWidth(1.0f);
//  float len = glm::length(vec);
//  if (len > 1.0f) {
//    vec /= len;
//  }
//  gl::Program::clear();
//
//  glLineWidth(2.0f + len);
//  glBegin(GL_LINES);
//  gl::color(col);
//  gl::vertex();
//  gl::vertex();
//  glEnd();
//
//  glLineWidth(1.0f);
//  glBegin(GL_LINE_STRIP);
//  gl::color(Colors::gray);
//  gl::vertex(glm::vec3());
//  gl::vertex(glm::vec3(vec.x, 0, vec.z));
//  gl::vertex(vec);
//  glEnd();
}

using namespace Text;

wstring toUtf16(const string & text) {
//    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
  wstring wide(text.begin(), text.end()); //= converter.from_bytes(narrow.c_str());
  return wide;
}

//
//static gl::GeometryPtr line;
//if (!line) {
//  Mesh mesh;
//  mesh.color = Colors::white;
//  mesh.addVertex(glm::vec3());
//  mesh.addVertex(GlUtils::X_AXIS * 2.0f);
//  mesh.fillColors();
//  line = mesh.getGeometry(GL_LINES);
//}
// Draw a line at the cursor
//{
//  gl::ProgramPtr lineProgram = GlUtils::getProgram(
//    Resource::SHADERS_SIMPLE_VS,
//    Resource::SHADERS_SIMPLE_FS);
//  renderGeometry(line, lineProgram);
//}

void GlUtils::renderString(const string & cstr, glm::vec2 & cursor,
    float fontSize, Resource fontResource) {
  getFont(fontResource)->renderString(toUtf16(cstr), cursor, fontSize);
}

void GlUtils::renderParagraph(const std::string & str) {
  glm::vec2 cursor;
  Text::FontPtr font = getFont(Resource::FONTS_INCONSOLATA_MEDIUM_SDFF);
  rectf bounds;
  wstring wstr = toUtf16(str);
  for (int i = 0; i < wstr.length(); ++i) {
    uint16_t wchar = wstr.at(i);
    rectf letterBound = font->getBounds(wchar);
//    extendLeft(bounds, letterBound);
    SAY("foo");
  }
  renderString(str, cursor);
}

void GlUtils::renderString(const string & str, glm::vec3 & cursor3d,
    float fontSize, Resource fontResource) {
  glm::vec4 target = glm::vec4(cursor3d, 0);
  target = gl::Stacks::projection().top() * gl::Stacks::modelview().top() * target;
  glm::vec2 newCursor(target.x, target.y);
  renderString(str, newCursor, fontSize, fontResource);
}

Text::FontPtr GlUtils::getFont(Resource fontName) {
  static map<Resource, FontPtr> fonts;
  if (fonts.find(fontName) == fonts.end()) {
    std::string fontData = Platform::getResourceData(fontName);
    FontPtr result(new Font());
    result->read((const void*)fontData.data(), fontData.size());
    fonts[fontName] = result;
  }
  return fonts[fontName];
}

Text::FontPtr GlUtils::getDefaultFont() {
  return getFont(Resource::FONTS_INCONSOLATA_MEDIUM_SDFF);
}

template<GLenum TYPE> struct ShaderInfo {
  time_t modified;
  gl::ShaderPtr shader;

  bool valid(Resource resource) {
    return shader &&
      (Resources::getResourceModified(resource) <= modified);
  }

  void compile(Resource resource) {
    SAY("Compiling shader file %s",
      Resources::getResourcePath(resource).c_str());

    std::string shaderSource =
      Platform::getResourceData(resource);
    modified = Resources::getResourceModified(resource);
    shader = ShaderPtr(new Shader(TYPE, shaderSource));
  }

  bool update(Resource resource) {
    if (!valid(resource)) {
      compile(resource);
      return true;
    }
    return false;
  }
};

ProgramPtr GlUtils::getProgram(Resource vs, Resource fs) {
  typedef ShaderInfo<GL_VERTEX_SHADER> VShader;
  typedef ShaderInfo<GL_FRAGMENT_SHADER> FShader;
  typedef map<Resource, VShader> VMap;
  typedef map<Resource, FShader> FMap;
  static VMap vShaders;
  static FMap fShaders;
  typedef map<string, ProgramPtr> ProgramMap;
  static ProgramMap programs;
  shader_error lastError(0, "none");
  VShader & vsi = vShaders[vs];
  FShader & fsi = fShaders[fs];
  string key = Resources::getResourcePath(vs) + ":" +
    Resources::getResourcePath(fs);
  try {
    bool relink = vsi.update(vs) | fsi.update(fs);
    if (relink || programs.end() == programs.find(key)) {
      cerr << "Relinking " + key << endl;
      programs[key] = ProgramPtr(new Program(vsi.shader, fsi.shader));
    }
  } catch (const shader_error & error) {
    lastError = error;
  }
  if (!programs[key]) {
    throw lastError;
  }
  GL_CHECK_ERROR;
  return programs[key];
}

const Mesh & GlUtils::getMesh(Resource res) {
  typedef map<Resource, MeshPtr> MeshMap;
  static MeshMap meshes;
  if (0 == meshes.count(res)) {
    std::string meshData = Platform::getResourceData(res);
    meshes[res] = MeshPtr(new Mesh(meshData));
  }
  return *meshes[res];
}

void GlUtils::renderSkybox(Resource firstResource) {
  GL_CHECK_ERROR;
  static gl::ProgramPtr skyboxProgram = getProgram(
    Resource::SHADERS_CUBEMAP_VS,
    Resource::SHADERS_CUBEMAP_FS);

  // Skybox texture
  MatrixStack & mv = gl::Stacks::modelview();
  mv.push().untranslate();

  // TODO better state management
  {
    glDisable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    getCubemapTextures(firstResource)->bind();
    renderGeometry(GlUtils::getCubeGeometry(), skyboxProgram);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
  }
  gl::TextureCubeMap::unbind();
  mv.pop();
}

gl::TextureCubeMapPtr GlUtils::getCubemapTextures(Resource firstResource) {
  typedef std::map<Resource, gl::TextureCubeMapPtr> Map;
  typedef Map::iterator MapItr;
  static Map skyboxMap;

  MapItr itr = skyboxMap.find(firstResource);
  if (skyboxMap.end() == itr) {
    GL_CHECK_ERROR;
    //glEnable(GL_TEXTURE_CUBE_MAP);
    GL_CHECK_ERROR;
    TextureCubeMapPtr texture(new TextureCubeMap());
    texture->bind();
    texture->parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    texture->parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    texture->parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    texture->parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    texture->parameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    GL_CHECK_ERROR;

    static GLenum RESOURCE_ORDER[] = {
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_X,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    };

    glm::ivec2 size;
    for (int i = 0; i < 6; ++i) {
      Resource image = static_cast<Resource>(firstResource + i);
      std::vector<unsigned char> data;
      GlUtils::getImageData(image, size, data);
      GL_CHECK_ERROR;
      texture->image2d(RESOURCE_ORDER[i], size, &data[0]);
      GL_CHECK_ERROR;
    }

    TextureCubeMap::unbind();
    skyboxMap[firstResource] = texture;
    return texture;
  }
  return itr->second;
}

gl::GeometryPtr GlUtils::getCubeGeometry() {
  static GeometryPtr cube;
  if (!cube) {
    cube = GeometryPtr(new Geometry(
        getCubeVertices(),
        getCubeIndices(),
        12, 0, GL_TRIANGLES, 3));
  }
  return cube;
}


static void cubeRecurse(int elapsed, int depth) {
  if (0 == depth) {
    return;
  }
  MatrixStack & mv = Stacks::modelview();
  static glm::vec3 AXES[] = { GlUtils::X_AXIS, GlUtils::Y_AXIS,
                              GlUtils::Z_AXIS };
  static glm::vec3 translation(0, 0, 1.5);

  const glm::vec3 & axis = AXES[rand() % 3];
  float angle = elapsed * 0.05f * ((rand() % 10) - 5);
  float scale = 0.7;

  mv.push().rotate(angle, axis).translate(translation).scale(scale);
  GlUtils::drawColorCube();
  cubeRecurse(elapsed, depth - 1);

  mv.pop().push().rotate(angle + 180, axis).translate(translation).scale(
      scale);
  GlUtils::drawColorCube();
  cubeRecurse(elapsed, depth - 1);
  mv.pop();
}

static void dancingCubes(int elapsed, int elements = 8) {
  MatrixStack & mv = Stacks::modelview();

  mv.push().scale(0.2f);
  GlUtils::drawColorCube();
  mv.pop();

  static glm::vec3 AXES[] = { GlUtils::X_AXIS, GlUtils::Y_AXIS,
                              GlUtils::Z_AXIS };
  srand(4);
  for (int i = 0; i < elements; ++i) {
    float angle = elapsed * 0.05f * (float) ((rand() % 6) - 2);
    float angle2 = elapsed * 0.05f * (float) ((rand() % 3) - 1);
    int axisRotate = rand();
    const glm::vec3 & axis = AXES[axisRotate % 3];
    const glm::vec3 & axis2 = AXES[(1 + axisRotate) % 3];
    int axisTranslate = axisRotate + rand() % 2;
    float sc = 1.0f / (float) (5 + rand() % 8);
    glm::vec3 tr = AXES[axisTranslate % 3];
    tr = tr / (float) (1 + (rand() % 6)) + (tr * 0.4f);
    mv.push().rotate(angle, axis).rotate(angle2, axis2);
    mv.push().translate(tr).scale(sc);
    GlUtils::drawColorCube();
    mv.pop().push().translate(-tr).scale(sc);
    GlUtils::drawColorCube();
    mv.pop();
  }
  for (int i = 0; i < elements; ++i) {
    mv.pop();
  }
}
